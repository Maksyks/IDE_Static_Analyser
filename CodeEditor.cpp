#include "CodeEditor.h"
#include <QPainter>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QRect>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QInputDialog>
#include <QMenu>
#include <QRegularExpression>
#include "IPluginInterface.h"
#include "mainwindow.h"
#include <QDebug>
#include "CHighlighter.h"

CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent), lineNumberArea(new LineNumberArea(this))
{
    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodeEditor::updateLineNumberArea);
    //connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
    this->setReadOnly(true);
    updateLineNumberAreaWidth(0);
    //highlightCurrentLine();
    QFont font;
    font.setFamily("Courier");  // Можно также "Consolas", "Monospace"
    font.setPointSize(12);
    this->setFont(font);
    new CHighlighter(document());
    setContextMenuPolicy(Qt::DefaultContextMenu);

}

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 15 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor("#1e1e1e"));

    QFont font = this->font();
    font.setPointSize(10);  // размер шрифта
    painter.setFont(font);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = static_cast<int>(blockBoundingGeometry(block)
                                   .translated(contentOffset()).top());
    int bottom = top + static_cast<int>(blockBoundingRect(block).height());

    QFontMetrics metrics(font);

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::white);
            QRect numberRect(0, top, lineNumberArea->width(), metrics.height());
            painter.drawText(numberRect, Qt::AlignCenter, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodeEditor::highlightLine(int blockNumber) {
    QList<QTextEdit::ExtraSelection> extras;
    QTextEdit::ExtraSelection sel;
    sel.format.setBackground(QColor(100, 149, 237, 80));
    sel.format.setProperty(QTextFormat::FullWidthSelection, true);
    QTextCursor cursor(document()->findBlockByNumber(blockNumber));
    sel.cursor = cursor;
    extras.append(sel);
    setExtraSelections(extras);
    currentHighlight = sel;
}

void CodeEditor::clearLineHighlight() {
    setExtraSelections({});
}

void CodeEditor::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Определить номер блока (строки)
        QTextCursor cursor = cursorForPosition(event->pos());
        int line = cursor.blockNumber();
        highlightLine(line);
    }
    QPlainTextEdit::mousePressEvent(event);
}

void CodeEditor::contextMenuEvent(QContextMenuEvent *event) {
    QMenu *menu = createStandardContextMenu();
    // Найти номер строки, на которую кликнули
    QTextCursor cursor = cursorForPosition(event->pos());
    int line = cursor.blockNumber() + 1; // 1-based
    QString text = document()->findBlockByNumber(line-1).text();

    // Регулярка для переменных (идентификаторы)
    static QRegularExpression re(R"((?:\b)([A-Za-z_][A-Za-z0-9_]*)(?:\b))");
    QSet<QString> vars;
    for (auto it = re.globalMatch(text); it.hasNext(); ) {
        auto match = it.next().captured(1);
        // Фильтруем ключевые слова (int, for, if, ...)
        static const QSet<QString> keywords = {
            // Основные
            "auto", "break", "case", "char",
            "const", "continue", "default", "do",
            "double", "else", "enum", "extern",
            "float", "for", "goto", "if",
            "int", "long", "register", "return",
            "short", "signed", "sizeof", "static",
            "struct", "switch", "typedef", "union",
            "unsigned", "void", "volatile", "while",
            "_Bool", "_Complex", "_Imaginary", "inline", "restrict",
            "_Alignas", "_Alignof", "_Atomic", "_Generic",
            "_Noreturn", "_Static_assert", "_Thread_local"
        };
        if (!keywords.contains(match)) vars.insert(match);
    }
    if (!vars.isEmpty()) {
        QAction *sliceAct = menu->addAction(tr("Сделать срез"));
        connect(sliceAct, &QAction::triggered, [this, line, vars]() {
            QString var;
            if (vars.size() == 1) {
                var = *vars.begin();
            } else {
                QStringList list = QStringList(vars.values());
                bool ok;
                var = QInputDialog::getItem(this,
                                            tr("Выберите переменную"),
                                            tr("Переменные в строке:"),
                                            list, 0, false, &ok);
                if (!ok || var.isEmpty()) return;
            }
            // Формируем критерий
            QString criterion = QString::number(line) + ":" + var;
            // Берём текст из редактора
            QString src = toPlainText();
            // Ищем плагин "Сделать срез"
            // Получаем указатель на главное окно IDE и его список плагинов
            if (auto *ide = qobject_cast<IDE*>(window())) {
                for (IPluginInterface* plug : ide->getPlugins()) {
                    if (plug->pluginName() == tr("Сделать срез")) {
                        qDebug() << "  -> Found slicer plugin!";
                        QString out = plug->process(src, line, var, this);
                        if (!out.isNull() && ide->getRightEditor())
                            ide->getRightEditor()->setPlainText(out);
                        break;
                    }
                }
            }

        });
    }
    menu->exec(event->globalPos());
    delete menu;
}

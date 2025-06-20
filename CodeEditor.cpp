#include "CodeEditor.h"
#include <QPainter>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QRect>

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

// void CodeEditor::highlightCurrentLine()
// {
//     QList<QTextEdit::ExtraSelection> extraSelections;

//     if (!isReadOnly()) {
//         QTextEdit::ExtraSelection selection;

//         selection.format.setBackground(QColor(100, 149, 237, 80));
//         selection.format.setProperty(QTextFormat::FullWidthSelection, true);
//         selection.cursor = textCursor();
//         selection.cursor.clearSelection();

//         extraSelections.append(selection);
//     }

//     setExtraSelections(extraSelections);
// }

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

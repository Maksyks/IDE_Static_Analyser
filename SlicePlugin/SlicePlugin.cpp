#include "SlicePlugin.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QTemporaryDir>
#include <QProcess>
#include <QDir>
#include <QCoreApplication>

QString SlicePlugin::askCriterion(QWidget *parent) {
    QMessageBox choice(parent);
    choice.setWindowTitle(tr("Критерий среза"));
    choice.setText(tr("Введите критерий вручную или выберите файл с критерием:"));
    QPushButton *btnManual = choice.addButton(tr("Вручную"), QMessageBox::AcceptRole);
    QPushButton *btnFile   = choice.addButton(tr("Из файла"), QMessageBox::AcceptRole);
    choice.addButton(tr("Отмена"), QMessageBox::RejectRole);
    choice.exec();
    if (choice.clickedButton() == nullptr || choice.clickedButton()->text() == tr("Отмена"))
        return QString();

    if (choice.clickedButton() == btnManual) {
        bool ok = false;
        QString text = QInputDialog::getText(parent,
                                             tr("Критерий среза"),
                                             tr("Введите критерий, например main:21:sum:"),
                                             QLineEdit::Normal,
                                             QString(), &ok);
        if (!ok || text.isEmpty()) return QString();
        return text;
    } else {
        QString fn = QFileDialog::getOpenFileName(parent,
                                                  tr("Выбрать файл с критерием"),
                                                  QString(),
                                                  tr("Текстовые файлы (*.txt);;Все файлы (*)"));
        if (fn.isEmpty()) return QString();
        QFile f(fn);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(parent, tr("Ошибка"), tr("Нельзя открыть файл"));
            return QString();
        }
        QTextStream in(&f);
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            QMessageBox::warning(parent, tr("Ошибка"), tr("Файл пуст"));
            return QString();
        }
        return line;
    }
}

QString SlicePlugin::process(const QString &input, QWidget *parent) {
    // 1) Выбор критерия
    QString criterion = askCriterion(parent);
    if (criterion.isEmpty())
        return {};

    // 2) Сохранение input как временный файл
    QTemporaryDir tmpd;
    if (!tmpd.isValid()) {
        QMessageBox::warning(parent, tr("Ошибка"), tr("Не удалось создать временную папку"));
        return {};
    }
    QString tmpC = tmpd.path() + "/input.c";
    QFile outF(tmpC);
    if (!outF.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(parent, tr("Ошибка"), tr("Не удалось сохранить временный .c"));
        return {};
    }
    QTextStream ts(&outF);
    ts << input;
    outF.close();

    // 3) Путь к script.sh в папке плагина
    QString appDir = QCoreApplication::applicationDirPath();
    QString winScript = QDir(appDir).filePath("plugins/slice.sh");

    // 4) Лямбда для конвертации путей через wslpath
    auto toWsl = [&](const QString &winPath) {
        QProcess p;
        p.start("wsl", {"wslpath", "-u", winPath});
        p.waitForFinished(5000);
        return QString::fromUtf8(p.readAllStandardOutput()).trimmed();
    };
    QString wslScript = toWsl(winScript);
    QString wslInput  = toWsl(tmpC);

    // 5) Запуск скрипта через WSL
    QProcess proc;
    QString cmd = QString("%1 '%2' '%3'")
                      .arg(wslScript)
                      .arg(wslInput)
                      .arg(criterion);
    proc.start("wsl", {"bash", "-lc", cmd});
    if (!proc.waitForFinished(60000)) {
        QMessageBox::warning(parent, tr("Ошибка"), tr("Скрипт среза не ответил"));
        return {};
    }
    if (proc.exitStatus() != QProcess::NormalExit || proc.exitCode() != 0) {
        QString err = proc.readAllStandardError();
        QMessageBox::warning(parent, tr("Ошибка среза"), err);
        return {};
    }

    // 6) Возврат stdout как текста
    QByteArray result = proc.readAllStandardOutput();
    return QString::fromUtf8(result);
}

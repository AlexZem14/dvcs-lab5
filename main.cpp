/*! \file main.cpp
 * Главный файл программы
 */

#include "synhra.h"

/*!
 * \brief Главная функция программы
 * \param [in] argc Количество переданных аргументов командной строки
 * \param [in] argv Массив аргументов командной строки
 * \return 0-при успешном выполнении, 1-в противном случае
 * 1 commit master
 * Аргументы командной строки:
 * argv[0] - аргумент содержащий имя запускаемой программы;
 * argv[1] – аргумент содержащий имя первого исходного файла;
 * argv[2] – аргумент содержащий имя второго исходного файла;
 * argv[3] – аргумент содержащий имя выходного файла
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    _setmode(_fileno(stderr), _O_U8TEXT); // Режим вывода в stderr в кодировке UTF-8
// 2 commit master
    error error;
    if(!checkArguments(argc, argv, error))
    {
        QString errorDescription = "Ошибка параметров программы: Нет ";
        if(error.type == errorType::noFileIn)
        {
            errorDescription += "входного ";
        }
        else if(error.type == errorType::noNameOut)
        {
            errorDescription += "выходного ";
        }
        errorDescription += "файла";
        qError(errorDescription);
        return 1;
    }
// 3 commit master
    QStringList matchList;
    if(!readMatch(argv[1], matchList, error))
    {
        QString errorDescription = "Ошибка параметров программы: Файл с соответствиями ";
        if(error.type == errorType::noExistFile)
        {
            errorDescription += "не существует";
        }
        else if(error.type == errorType::noOpenFile)
        {
            errorDescription += "не получается открыть";
        }
        qError(errorDescription);
        return 1;
    }
// 4 commit master
    QString stringChain;
    if(!readChain(argv[2], stringChain, error))
    {
        QString errorDescription = "Ошибка параметров программы: Файл c последовательностью действий ";
        if(error.type == errorType::noExistFile)
        {
            errorDescription += "не существует";
        }
        else if(error.type == errorType::noOpenFile)
        {
            errorDescription += "не получается открыть";
        }
        qError(errorDescription);
        return 1;
    }

    QMap<int, QString> match;
	// master commmit 5
    if(!putToMap(matchList, match))
        return 1;
// master commit 6
    QVector<int> chain;
    if(!putToVector(stringChain, chain, match))
        return 1;
// master commit 7
    QVector<QString> mappedModes;
    matchModes(match, chain, mappedModes);
// master commit 8
    if(!writeData(mappedModes,argv[3]))
        return 1;
    return 0;
}

#include <QCoreApplication>
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include <QTextStream>
#include <stdio.h>
#include <QDebug>
#include <QDir>

QTextStream cout(stdout, QIODevice::WriteOnly);
QTextStream cerr(stderr, QIODevice::WriteOnly);

//overload operator<<, otherwise Qt would not recognize OFString.
QDebug operator<<(QDebug dbg, const OFString &ofString)
{
    dbg.nospace() << ofString.c_str();
    return dbg.space();
}

//overload operator<<, otherwise Qt would not recognize OFString.
QTextStream& operator<<(QTextStream &outstream, OFString &ofString)
{
    outstream << ofString.c_str();
    return outstream;
}

void outDcmInfo(const char *filePath)
{
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(filePath);
    if (status.good())
    {
        OFString patientsName;
        if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientsName).good())
        {
//            qDebug() << "Patient's Name: " << patientsName;
            cout << "Patient's Name: " << patientsName << endl;//endl is essential, otherwise this line would be overlapped. But it is not essential when qDebug().
        }
        else
            cerr << "Error: cannot access Patient's Name!" << endl;

        OFString studyID;
        if (fileformat.getDataset()->findAndGetOFString(DCM_StudyID, studyID).good())
        {
            cout << "studyID: " << studyID << endl;
        }
        else
            cerr << "Error: cannot access studyID!" << endl;

        OFString seriesNumber;
        if (fileformat.getDataset()->findAndGetOFString(DCM_SeriesNumber, seriesNumber).good())
        {
            cout << "seriesNumber: " << seriesNumber << endl;
        }
        else
            cerr << "Error: cannot access seriesNumber!" << endl;

        OFString acquisitionNumber;
        if (fileformat.getDataset()->findAndGetOFString(DCM_AcquisitionNumber, acquisitionNumber).good())
        {
            cout << "acquisitionNumber: " << acquisitionNumber << endl;
        }
        else
            cerr << "Error: cannot access acquisitionNumber!" << endl;

        OFString instanceNumber;//Image No.
        if (fileformat.getDataset()->findAndGetOFString(DCM_InstanceNumber, instanceNumber).good())
        {
            cout << "instanceNumber: " << instanceNumber << endl;
        }
        else
            cerr << "Error: cannot access instanceNumber!" << endl;

        OFString windowCenter;
        if (fileformat.getDataset()->findAndGetOFString(DCM_WindowCenter, windowCenter).good())
        {
            cout << "WL: " << windowCenter << endl;
        }
        else
            cerr << "Error: cannot access windowCenter!" << endl;

        OFString windowWidth;
        if (fileformat.getDataset()->findAndGetOFString(DCM_WindowWidth, windowWidth).good())
        {
            cout << "WW: " << windowWidth << endl;
        }
        else
            cerr << "Error: cannot access windowWidth!" << endl;

        OFString rows;
        if (fileformat.getDataset()->findAndGetOFString(DCM_Rows, rows).good())
        {
            cout << "rows: " << rows << endl;
        }
        else
            cerr << "Error: cannot access rows!" << endl;

        OFString columns;
        if (fileformat.getDataset()->findAndGetOFString(DCM_Columns, columns).good())
        {
            cout << "columns: " << columns << endl;
        }
        else
            cerr << "Error: cannot access columns!" << endl;

        OFString numberOfFrames;
        if (fileformat.getDataset()->findAndGetOFString(DCM_NumberOfFrames, numberOfFrames).good())
        {
            cout << "numberOfFrames: " << numberOfFrames << endl;
        }
        else
            cerr << "Error: cannot access numberOfFrames!" << endl;

        OFString samplesPerPixel;
        if (fileformat.getDataset()->findAndGetOFString(DCM_SamplesPerPixel, windowWidth).good())
        {
            cout << "samplesPerPixel: " << samplesPerPixel << endl;
        }
        else
            cerr << "Error: cannot access samplesPerPixel!" << endl;

        OFString samplesPerPixelUsed;
        if (fileformat.getDataset()->findAndGetOFString(DCM_SamplesPerPixelUsed, windowWidth).good())
        {
            cout << "samplesPerPixelUsed: " << samplesPerPixelUsed << endl;
        }
        else
            cerr << "Error: cannot access samplesPerPixelUsed!" << endl;

        OFString photometricInterpretation;
        if (fileformat.getDataset()->findAndGetOFString(DCM_PhotometricInterpretation, windowWidth).good())
        {
            cout << "photometricInterpretation: " << photometricInterpretation << endl;
        }
        else
            cerr << "Error: cannot access photometricInterpretation!" << endl;
    }
    else
        cerr << "Error: cannot read DICOM file (" << status.text() << ")" << endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);  

//    QTextStream cin(stdin, QIODevice::ReadOnly);
//    QTextStream cout(stdout, QIODevice::WriteOnly);
//    QTextStream cerr(stderr, QIODevice::WriteOnly);

    cout << "************************Begin************************" << endl;

    QString strDir("D:/programs/dcmfiles/");
    QDir *dir = new QDir(strDir);
    QStringList filter;
    filter << "*.dcm";
    dir->setNameFilters(filter);
    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    int count = fileInfo->count();

    QString strFileName;
    for(int i = 0; i < count; i++)
    {
        strFileName = fileInfo->at(i).filePath();
        std::string str = strFileName.toStdString();
        cout << str.c_str() << endl;
        outDcmInfo(str.c_str());
        cout << endl;
    }

    cout << "************************End************************" << endl;

//    system("pause");

    return a.exec();
}

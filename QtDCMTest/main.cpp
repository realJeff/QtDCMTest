#include <QCoreApplication>
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
//#include <QTextStream>
//#include <stdio.h>
#include <QDebug>


//overload operator<<, otherwise Qt would not recognize OFString.
QDebug operator<<(QDebug dbg, const OFString &ofString)
{
    dbg.nospace() << ofString.c_str();
    return dbg.space();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "************************Begin************************";

//    QTextStream cin(stdin, QIODevice::ReadOnly);
//    QTextStream cout(stdout, QIODevice::WriteOnly);
//    QTextStream cerr(stderr, QIODevice::WriteOnly);


    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile("test.dcm");
    if (status.good())
    {
        OFString patientsName;
        if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientsName).good())
        {
            qDebug() << "Patient's Name: " << patientsName;
        }
        else
            qDebug() << "Error: cannot access Patient's Name!";

        OFString studyID;
        if (fileformat.getDataset()->findAndGetOFString(DCM_StudyID, studyID).good())
        {
            qDebug() << "studyID: " << studyID;
        }
        else
            qDebug() << "Error: cannot access studyID!";

        OFString seriesNumber;
        if (fileformat.getDataset()->findAndGetOFString(DCM_SeriesNumber, seriesNumber).good())
        {
            qDebug() << "seriesNumber: " << seriesNumber;
        }
        else
            qDebug() << "Error: cannot access seriesNumber!";

        OFString acquisitionNumber;
        if (fileformat.getDataset()->findAndGetOFString(DCM_AcquisitionNumber, acquisitionNumber).good())
        {
            qDebug() << "acquisitionNumber: " << acquisitionNumber;
        }
        else
            qDebug() << "Error: cannot access acquisitionNumber!";

        OFString instanceNumber;//Image No.
        if (fileformat.getDataset()->findAndGetOFString(DCM_InstanceNumber, instanceNumber).good())
        {
            qDebug() << "instanceNumber: " << instanceNumber;
        }
        else
            qDebug() << "Error: cannot access instanceNumber!";

        OFString windowCenter;
        if (fileformat.getDataset()->findAndGetOFString(DCM_WindowCenter, windowCenter).good())
        {
            qDebug() << "WL: " << windowCenter;
        }
        else
            qDebug() << "Error: cannot access windowCenter!";

        OFString windowWidth;
        if (fileformat.getDataset()->findAndGetOFString(DCM_WindowWidth, windowWidth).good())
        {
            qDebug() << "WW: " << windowWidth;
        }
        else
            qDebug() << "Error: cannot access windowWidth!";

        OFString rows;
        if (fileformat.getDataset()->findAndGetOFString(DCM_Rows, rows).good())
        {
            qDebug() << "rows: " << rows;
        }
        else
            qDebug() << "Error: cannot access rows!";

        OFString columns;
        if (fileformat.getDataset()->findAndGetOFString(DCM_Columns, columns).good())
        {
            qDebug() << "columns: " << columns;
        }
        else
            qDebug() << "Error: cannot access columns!";

        OFString numberOfFrames;
        if (fileformat.getDataset()->findAndGetOFString(DCM_NumberOfFrames, numberOfFrames).good())
        {
            qDebug() << "numberOfFrames: " << numberOfFrames;
        }
        else
            qDebug() << "Error: cannot access numberOfFrames!";

        OFString samplesPerPixel;
        if (fileformat.getDataset()->findAndGetOFString(DCM_SamplesPerPixel, windowWidth).good())
        {
            qDebug() << "samplesPerPixel: " << samplesPerPixel;
        }
        else
            qDebug() << "Error: cannot access samplesPerPixel!";

        OFString samplesPerPixelUsed;
        if (fileformat.getDataset()->findAndGetOFString(DCM_SamplesPerPixelUsed, windowWidth).good())
        {
            qDebug() << "samplesPerPixelUsed: " << samplesPerPixelUsed;
        }
        else
            qDebug() << "Error: cannot access samplesPerPixelUsed!";

        OFString photometricInterpretation;
        if (fileformat.getDataset()->findAndGetOFString(DCM_PhotometricInterpretation, windowWidth).good())
        {
            qDebug() << "photometricInterpretation: " << photometricInterpretation;
        }
        else
            qDebug() << "Error: cannot access photometricInterpretation!";
    }
    else
        qDebug() << "Error: cannot read DICOM file (" << status.text() << ")";

    qDebug() << "************************End************************";

//    system("pause");

    return a.exec();
}

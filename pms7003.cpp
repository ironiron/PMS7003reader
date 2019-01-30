#include "pms7003.h"

#include <qdebug.h>

PMS7003::PMS7003(QObject *parent) : QObject(parent)
{

}

void PMS7003::getData()
{
    //return data;
}

void PMS7003::getData(char *Bytes)
{
    this->processBytes(Bytes);
    //return data;
}

void PMS7003::processBytes(char *Bytes)
{
    int index;

    //qDebug() << ("readBytesa:") << serialPort.read(Bytes,65);

    qDebug() << ("Bytes:") << int(Bytes[0]);
    qDebug() << ("Bytes1:") << int(Bytes[1]);
    qDebug() << ("Bytes2:") << int(Bytes[2]);
    qDebug() << ("Bytes3:") << int(Bytes[3]);
    qDebug() << ("Bytes4:") << int(Bytes[4]);
    qDebug() << ("Bytes5:") << int(Bytes[5]);
    qDebug() << ("Bytes6:") << int(Bytes[6]);
    qDebug() << ("Bytes7:") << int(Bytes[7]);
    qDebug() << ("Bytes8:") << int(Bytes[8]);
    qDebug() << ("Bytes9:") << int(Bytes[9]);
    qDebug() << ("Bytes10") << int(Bytes[10]);
    qDebug() << ("Bytes11:") << int(Bytes[11]);
    qDebug() << ("Bytes12:") << int(Bytes[12]);
    qDebug() << ("Bytes13:") << int(Bytes[13]);
    qDebug() << ("Bytes14:") << int(Bytes[14]);
    qDebug() << ("Bytes15:") << int(Bytes[15]);
    qDebug() << ("Bytes16:") << int(Bytes[16]);
    qDebug() << ("Bytes17:") << int(Bytes[17]);
    qDebug() << ("Bytes18:") << int(Bytes[18]);
    qDebug() << ("Bytes19:") << int(Bytes[19]);
    qDebug() << ("Bytes20:") << int(Bytes[20]);
    qDebug() << ("Bytes21:") << int(Bytes[21]);
    qDebug() << ("Bytes22:") << int(Bytes[22]);
    qDebug() << ("Bytes23:") << int(Bytes[23]);
    qDebug() << ("Bytes24:") << int(Bytes[24]);
    qDebug() << ("Bytes25:") << int(Bytes[25]);
    qDebug() << ("Bytes26:") << int(Bytes[26]);
    qDebug() << ("Bytes27:") << int(Bytes[27]);
    qDebug() << ("Bytes28:") << int(Bytes[28]);
    qDebug() << ("Bytes29:") << int(Bytes[29]);
    qDebug() << ("Bytes30:") << int(Bytes[30]);
    qDebug() << ("Bytes31:") << int(Bytes[31]);

   // while(Bytesaindex<50)
   // {
   //     if(Bytes[Bytesaindex]==0x42)
  //  }
      if(Bytes[0]!=0x42||Bytes[1]!=0x4d)
      {
          qDebug() << ("ERRRRRRORRRRRR");

      }


      unsigned int crc=PCNT_5_0=uint8_t(Bytes[30])<<8|uint8_t(Bytes[31]);
      unsigned int crc2=0;
      qDebug() << ("crc") << crc;
      for (index=0;index<30;index++)
      {
          crc2=crc2+uint8_t(Bytes[index]);
      }

      this->PM1=uint8_t(Bytes[4])<<8|uint8_t(Bytes[5]);
      PM2_5=uint8_t(Bytes[6])<<8|uint8_t(Bytes[7]);
      PM10=uint8_t(Bytes[8])<<8|uint8_t(Bytes[9]);

      PM1atm=uint8_t(Bytes[10])<<8|uint8_t(Bytes[11]);
      PM2_5atm=uint8_t(Bytes[12])<<8|uint8_t(Bytes[13]);
      PM10atm=uint8_t(Bytes[14])<<8|uint8_t(Bytes[15]);

      PCNT_0_3=uint8_t(Bytes[16])<<8|uint8_t(Bytes[17]);
      PCNT_0_5=uint8_t(Bytes[18])<<8|uint8_t(Bytes[19]);
      PCNT_1_0=uint8_t(Bytes[20])<<8|uint8_t(Bytes[21]);
      PCNT_2_5=uint8_t(Bytes[22])<<8|uint8_t(Bytes[23]);
      PCNT_5_0=uint8_t(Bytes[24])<<8|uint8_t(Bytes[25]);
      PCNT_10_0=uint8_t(Bytes[26])<<8|uint8_t(Bytes[27]);
}





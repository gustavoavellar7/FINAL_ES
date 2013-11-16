#include "connection.h"

Connection::Connection(QTcpSocket *_socket)
{
    socket = _socket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(recv()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
    this->indice_lista_conexion = -1;

}

void Connection::recv() {
        message.append(socket->readAll());
                parseMessage(QString(message));

}

void Connection::parseMessage(QString datos) {
    /*//qDebug() << datos;
    QString temp;
    //printf("Name: %s\n", name.at(7));
    //QString::SectionFlag flag = QString::SectionSkipEmpty;
    temp = datos;
    x=temp.split(" ")[2].toInt();
    y=temp.split(" ")[3].toInt();
    qDebug() <<x;
    qDebug() <<y;*/
    emit newMessage(this,datos);
    /*
    for (int i = datos.size()-1; i >= 0; i--){
        if (temp.at(i).toAscii() == '|'){
            temp.remove(0, i+1);

            indice++;
            temp= datos;
            temp.remove(i,datos.size()-1);
            //std::cout << resul.at(i).toAscii() << std::endl;
        }
    }
    //printf("Name: %s\n", resul.at(1).);


       if(msg.startsWith("MSG:"))
       {
           msg = "MSGFROM:" + this->nick+ ":" + msg.mid(4);
           emit newMessage(this,msg);
       }
       else
          if(msg.startsWith("CON:")) {
                // Obtener el nick
                QString elresto = msg.mid(4 );
                this->nick = elresto.mid(0,elresto.length()-2) ;
                emit connected(this, nick);
                //sendMessage("CONACCEPT:ok\n\r");
            }

                int start = msg.indexOf("Nick: ");
                int end = msg.indexOf("\n", start);
                QString newNick = msg.mid(start + 6, end - start - 6);
*/

}
void Connection::sendMessage(QString msg) {
    //READ: Si el socket de la conexion es valido entonces enviar el mensaje
    // Pero convertirlo en ASCII
    if (socket->isValid())
        socket->write(msg.toAscii());

}
void Connection::disconnect() {
       //READ: Emitir una señal al server para desconectarse
        emit disconnected(this, nick);

}



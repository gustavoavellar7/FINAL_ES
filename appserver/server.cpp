#include "server.h"

Server::Server()
{
    //READ: Iinicializar la bandera en false, enlazar o conectar el evento o señal
    // de newConnection que genere una instancia de esta clase y que la reciba y procese
    // esta misma instancia por el SLOT newConnection ..
    // Limpiar la lista de conexiones
    // Hacer que el apuntador al TextEdit(Log) sea nulo
    this->server_started = false;
    connect(this, SIGNAL(newConnection()), this, SLOT(newConnection()));
    this->Lista_Conexiones.clear();
    this->log = 0;
    this->busy=false;
    this->x=500;
    this->y=200;
}
Server::~Server()
{
    //READ: Simplemente llamar al metodo STOP que hace toda la limpieza
    this->stop();
}

void Server::start(int port)
{
    //READ: Bueno iniciar el server siempre y cuando NO se haya iniciado previamente
    // para eso se revisa la bandera. Luego ejecutamos el metodo LISTEN para escuchar
    // en el puerto que recibe de parametro, en caso que no pueda escuchar en ese
    // puerto porque por ejemplo puede que ya este ocupado entonces, mostrar un mensaje
    // y dejar en false la bandera.
    // Si logra arranca, entonces colocar la bandera en True, instancia la nickList
    // Limpia la lista de conexiones y muestra un mensaje en el LOG.
    if (this->server_started==false)
    {
        if (listen(QHostAddress::Any, port))
        {
           this->server_started = true;

           this->Lista_Conexiones.clear();
           this->log->append(tr("Servidor iniciado en puerto :%1 ").arg(port));
        }
        else
        {
            this->server_started = false;
            this->log->append(tr("Servidor no se pudo iniciar :%1 ").arg(this->errorString()));
        }
    }

}
void Server::stop()
{
    if (this->server_started)
    {

      this->server_started = false;
      delete this->nickList;
      // Limpiar la lista de conexiones

       while (!this->Lista_Conexiones.isEmpty())
         {
            // this->Lista_Conexiones.at(0)->disconnect(); //Desconectar la conexion

             Connection *cTemp= this->Lista_Conexiones.takeFirst();  // Libera el apuntador
             cTemp->sendMessage("SERVERSTOP:\n\r");
             delete cTemp;
         }
        //Cerrar el socket del server
        this->close();
        this->log->append(tr("Servidor detenido!!! "));
    }

}
bool Server::getStatus()
{
    return this->server_started;
}
void Server::newConnection() {
        // Cuando se crea la conexion la enlazo agregandola a lista de conexiones
        Connection *con = new Connection(nextPendingConnection());
         // Agregarla a la lista de conexiones
        this->Lista_Conexiones.push_back(con);
        // Decirle a la conexion en que posicion de la lista la agregaron
        con->indice_lista_conexion = this->Lista_Conexiones.count()-1;

        connect(con, SIGNAL(newMessage(Connection*,QString)), this, SLOT(procesarMensaje(Connection*,QString)));
       // connect(this, SIGNAL(newMessage(QString)), con, SLOT(sendMessage(QString)));
        //connect(con, SIGNAL(connected(Connection*, QString)), this, SLOT(connected(Connection*, QString)));
       // connect(con, SIGNAL(disconnected(Connection*, QString)), this , SLOT(disconnected(Connection*, QString)));

        this->log->append("Nueva conexion..." + con->socket->peerAddress().toString());


}




/*void Server::procesarMensaje(Connection *con, QString mensaje)
{
    int i=0;
    while (i<this->Lista_Conexiones.count())
   {
        // Enviar al resto lo que recibimos de con, inclusive al mismo (ECHO)
        if(this->Lista_Conexiones.at(i)->socket->isValid())
        {
            this->log->append(con->nick+">>Enviando:(" +this->Lista_Conexiones.at(i)->nick+"):" + mensaje);
            this->Lista_Conexiones.at(i)->sendMessage(mensaje);
         }
    i++;
   }

}*/
void Server::procesarMensaje(Connection *con, QString datos)
{
    if(!busy){
    //qDebug() << datos;
    QString temp;
    //printf("Name: %s\n", name.at(7));
    //QString::SectionFlag flag = QString::SectionSkipEmpty;
    temp = datos;
    x=temp.split(" ")[2].toInt();
    y=temp.split(" ")[3].toInt();
    }
   /* qDebug()<<"ESTOS SON LOS DATOS";
    qDebug() <<x;
    qDebug() <<y;*/
    //int i=0;
   // while (i<this->Lista_Conexiones.count())
  // {
        // Enviar al resto lo que recibimos de con, inclusive al mismo (ECHO)
     //   if(this->Lista_Conexiones.at(i)->socket->isValid())
      //  {
    //        this->log->append(con->nick+">>Enviando:(" +this->Lista_Conexiones.at(i)->nick+"):" + mensaje);
     //       this->Lista_Conexiones.at(i)->sendMessage(mensaje);
    //     }
   // i++;
  // }

}

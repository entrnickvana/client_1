#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>

/*
  The ClientSocket class provides a socket that is connected with a client.
  For every client that connects to the server, the server creates a new
  instance of this class.
*/
class ClientSocket : public QSocket
{
    Q_OBJECT
public:
    ClientSocket( int sock, QObject *parent=0, const char *name=0 ) : QSocket( parent, name );

    ~ClientSocket()
    {
    }

signals:
    void logText( const QString& );

private slots:
    void readClient()
    {
        QTextStream ts( this );
        while ( canReadLine() ) {
            QString str = ts.readLine();
            emit logText( tr("Read: '%1'\n").arg(str) );

            ts << line << ": " << str << endl;
            emit logText( tr("Wrote: '%1: %2'\n").arg(line).arg(str) );

            line++;
        }
    }

private:
    int line;
};

#endif // CLIENTSOCKET_H

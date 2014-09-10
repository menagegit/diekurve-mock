#include "network_layer.h"

#include <QDebug>
#include <stdint.h>

network_layer_t::network_layer_t(qint16 p):
    sock(), port(p), handler_data(NULL)
{
    sock.bind(port);

    /* handler for incoming data */
    QObject::connect(&(this->sock), SIGNAL(readyRead()),
                this, SLOT(signal_data_arrived()));
}

bool network_layer_t::write_data(packet_t *p, const char *ip_dest)
{
    int ret = 0;
    QHostAddress dest = QHostAddress(QString(ip_dest));

    ret = sock.writeDatagram((const char*) &(p->data), p->len, dest, port);

    if(ret < 0)
        { qDebug() << sock.errorString(); return false; }

    return true;
}

void network_layer_t::set_incomming_data_handler(data_arrived_handler* h, void *d)
{
    handler = h;
    handler_data = d;
}

void network_layer_t::signal_data_arrived()
{
    packet_t *p;
    QHostAddress qaddr;
    quint16 prt = 0;
    uint64_t addr;

    p = allocate_packet();
    if(p == NULL)
    {
        qDebug() << "Impossible to allocate memory for incomming packet. Dropped.";
        sock.readDatagram(NULL, 0); /* drop packet */
        return ;
    }

    p->len = sock.readDatagram((char*) p->data, max_packet_size(), &qaddr, &prt);

    if(p->len < 0) /* error - TODO handle better */
        { qDebug() << sock.errorString(); }

    if(qaddr.protocol() == QAbstractSocket::IPv6Protocol)
        { addr = 0; /*qaddr.toIPv6Address();*/ } /* TODO parse to long */
    else
        { addr = qaddr.toIPv4Address(); }

    if(this->handler != NULL)
        { (*handler)(handler_data, p, addr, prt); }
}

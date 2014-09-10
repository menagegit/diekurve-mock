#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H

#include <QUdpSocket>

#include "packet.h"

typedef void (*data_arrived_handler)(void*, packet_t*, uint64_t, uint16_t);

class network_layer_t: public QObject
{
    Q_OBJECT
private:
    QUdpSocket sock;
    qint16 port;
    /* only one handler because it must by able to modify the packet */
    data_arrived_handler* handler;
    void *handler_data;

private slots:
    void signal_data_arrived();

public:
    network_layer_t(qint16 port);

    bool write_data(packet_t*, const char *ip_dest);
    void set_incomming_data_handler(data_arrived_handler*, void*);
};

#endif // NETWORK_LAYER_H

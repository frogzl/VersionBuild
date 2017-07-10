#ifndef SERVICELISTENER_H
#define SERVICELISTENER_H

#include <QThread>

class ServiceListener : public QThread
{
	Q_OBJECT
public:
    ServiceListener(void);
    ~ServiceListener();
protected:
	void run();
private:
    
};

#endif // SERVICELISTENER_H

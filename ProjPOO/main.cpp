#include "startingwindow.h"
#include <QApplication>
#include "includes.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartingWindow w;
    w.show();
   /* Event e;
    e.basicEventInformation();
    Event e1("HOW YOU DOIN >?!!");
    Event e2("D0l0r3sH@ze");
    Event e3("GOD FORBIDHEJE");
    Log l;
    l.addLog(e1);
    l.addLog(e2);
    l.addLog(e3);
    l.printBasicLog();
    EventQueue someEventQueue;
    someEventQueue.addEvent(e);
    LogHandler someLogHandler;
    l.printCurrentLogs();
    someLogHandler.updateLog(someLogHandler.getTime(), l);
*/
    User u1("Georgica") , u2("Vasile","Georgica") , u3("Ionel","Georgica"), u4("GICA","Vasile");
    User u5("IOCLA","GICA") , u6("IOI","IOCLA");
     Administrator aa("Costica");

    // qDebug() << typeid(u1).name();
     //QString q1 = typeid(aa).name();
    //qDebug() << q1.contains("Administrator");

   // aa.getFirma()->setBoss(aa);
    Node *b ,*ddd,*dddd;
    Node1 *pdf;
        b = new Node;
        b->user = u1;
        b->father = NULL;
    Node *c, *d , *eee;
        c = new Node ; d = new Node , eee= new Node;
        c->user = u2; d->user = u3; eee->user = u4;
        ddd = new Node ; dddd = new Node ;
        ddd->user = u5;
        dddd->user = u6;
    Firma *f7 = new Firma(u1);

    //qDebug () << f7->getTree()->getNode()->user.getUserName();
    Tree f(b);

    pdf = new Node1;
    pdf->user = &aa;
    pdf->father =NULL;
    Tree f1(pdf);
    Firma *f8 = new Firma(&f);


    //qDebug () << f7->getTree()->getNode()->user.getUserName();
    //qDebug() << d->user.getUserName();
    //f1.add(b,"Costica");
    f.add(c,"Georgica");
    f.add(d,"Georgica");
    f.add(eee,"Vasile");
    f.add(ddd,"GICA");
    f.add(dddd,"IOCLA");
    //qDebug() << f1.traverse("Georgica")->user.getUserName();
   // f8->getTree()->find("GICA")->user.getUserName();
    User u7("VASILON",f8,"GICA");
    Node *nnn = new Node;
    nnn->user = u7;
    u7.getFirma()->getTree()->add(nnn,u7.getBoss());
    u7.getFirma()->getTree()->traverse();
    qDebug() << u7.getFirma()->getTree()->check("prunoiu");
    //qDebug () << u7.getFirma()->getTree()->find("VASILON")->user.getUserName();
    //qDebug() << u7.getFirma()->getTree()->check("GIGEL");
    //u7.getFirma()->getTree()->traverse();
    return a.exec();
}

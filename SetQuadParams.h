#ifndef SETQUADPARAMS_H
#define SETQUADPARAMS_H

#include <QWidget>
#include <SendCommand.h>
#include <serialcontroller.h>

namespace Ui {
class SetQuadParams;
}

class SetQuadParams : public QWidget
{
    Q_OBJECT

public:
    SetQuadParams(SerialController * serialController, QWidget *parent = nullptr);
    ~SetQuadParams();
signals:
    void sendCommand(ReceiveInformations quadCommand);
public slots:
    void settingCameSlot(SendInformations info);
    void sendAltitudePid();
    void sendRollAndPitchPid();
private:
    Ui::SetQuadParams *ui;
    SerialController* m_serialController;
};

#endif // SETQUADPARAMS_H

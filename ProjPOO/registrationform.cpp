#include "registrationform.h"
#include "ui_registrationform.h"

RegistrationForm::RegistrationForm(QMainWindow *qm, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(cancelButton()));
    startWindow = qm;
    setFixedSize(this->size());
    connect(ui->regBtn, SIGNAL(clicked()), this, SLOT(registerUser()));
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::cancelButton() {
    startWindow->show();
    this->close();
}

void RegistrationForm::registerUser() {
    ui->userTb->setStyleSheet("background-color: white; color: black;");
    ui->passTb->setStyleSheet("background-color: white; color: black;");
    ui->emailTb->setStyleSheet("background-color: white; color: black;");
    ui->userError->setStyleSheet("color: rgba(255, 0, 0, 0);");
    ui->passError->setStyleSheet("color: rgba(255, 0, 0, 0);");
    ui->emError->setStyleSheet("color: rgba(255, 0, 0, 0);");
    ui->confError->setStyleSheet("color: rgba(255, 0, 0, 0);");
    ui->emcoError->setStyleSheet("color: rgba(255, 0, 0, 0);");

    if (!Operations::isValidUser(ui->userTb->text())) {
        ui->userTb->setStyleSheet("background-color:rgba(255, 150, 150, 1); color: black;");
        ui->userError->setText("Username must have 3+ characters; alphanumerical allowed.");
        ui->userError->setStyleSheet("color:rgba(255, 0, 0, 1);");
    }

    else if (!Operations::isValidPassword(ui->passTb->text())) {
        ui->passTb->setStyleSheet("background-color:rgba(255, 150, 150, 1); color: black;");
        ui->passError->setText("Password must be 6+ characters; alphanumerical, minimum a digit.");
        ui->passError->setStyleSheet("color:rgba(255, 0, 0, 1);");
    }

    else if (ui->passcTb->text() != ui->passTb->text()) {
        ui->confError->setText("The two passwords are not identical.");
        ui->confError->setStyleSheet("color:rgba(255, 0, 0, 1);");
    }

    else if (!Operations::isValidEmail(ui->emailTb->text())) {
        ui->emailTb->setStyleSheet("background-color:rgba(255, 150, 150, 1); color: black;");
        ui->emError->setText("Please insert a valid email address.");
        ui->emError->setStyleSheet("color:rgba(255, 0, 0, 1);");
        qDebug() << "invalid mail";
    }

    else if (ui->emailconfTb->text() != ui->emailTb->text()) {
        ui->emcoError->setText("The two email addresses must be identical.");
        ui->emcoError->setStyleSheet("color:rgba(255, 0, 0, 1);");
    }

    else {
        if (UserManager::findUserByName(ui->userTb->text())) {
            ui->userError->setText("This username was taken by another user.");
            ui->userError->setStyleSheet("color: rgba(255, 0, 0, 1);");
        } else if (UserManager::findUserByMail(ui->emailTb->text())) {
            ui->emError->setText("There is already a user registered with this email.");
            ui->emError->setStyleSheet("color: rgba(255, 0, 0, 1);");
        } else {
            UserManager::openDatabaseConn();
            UserManager::registerUser(ui->userTb->text(), ui->passTb->text(), ui->emailTb->text());
            QTimer *timer = new QTimer();
            connect(timer, SIGNAL(timeout()), this, SLOT(redirect()));
            timer->setSingleShot(false);
            timer->start(3000);
            ui->emcoError->setText("Registration succesful! Redirecting to starting window...");
            ui->emcoError->setStyleSheet("color: rgba(0, 180, 0, 1);");
            ui->regBtn->setEnabled(false);
            ui->cancelBtn->setEnabled(false);
        }
    }
}

void RegistrationForm::redirect() {
    startWindow->show();
    this->close();
}
#include "analizador.h"
#include "ui_analizador.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <QFileDialog>
#include <QMessageBox>
using namespace std;

int matriz [20][33]{
    {1,2,3,506,506,2,1,15,17,105,106,108,19,107,128,13,14,12,9,11,10,129,130,121,122,119,120,124,123,506,0,0,0},
    {1,2,2,2,100,2,1,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
    {2,2,2,2,101,2,2,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
    {102,102,3,102,4,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102},
    {500,500,5,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500},
    {103,103,5,103,103,6,6,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103},
    {501,501,8,501,501,501,501,501,501,7,7,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501},
    {502,502,8,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502},
    {104,104,8,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
    {109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,110,109,109,109,109,109,109,109,109,109,109,109,109,109,109},
    {111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,112,111,111,111,111,111,111,111,111,111,111,111,111,111,111},
    {113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,114,113,113,113,113,113,113,113,113,113,113,113,113,113,113},
    {116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,115,116,116,116,116,116,116,116,116,116,116,116,116,116},
    {503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,117,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503},
    {504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,118,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504},
    {16,16,16,16,16,16,16,505,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
    {507,507,507,507,507,507,507,125,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507},
    {17,17,17,17,17,17,17,17,18,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17},
    {126,126,126,126,126,126,126,126,17,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126},
    {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,127,19,19}
};

string reservadas[17]={"class","endclass","int","float","char","string","bool","if","else","do","while","input","output","def","to","break","loop"};
char minusculas[25]={'a','b','c','d','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char may[25]={'A','B','C','D','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

string le,pal;
std::string cadToken;
std::string cadError;
int edo,rel,longi,inicio,final;
char car;


int relaciona(char car){

    for(int j=0;j<25;j++){
        if(car==minusculas[j]){
            return 0;
        }else if(car==may[j]){
            return 1;
        }
    }

    int i=car-'0';
    if (i>=0 && i<=9){
        return 2;
    }

    switch (car){
        case '_':
            return 3;
            break;
        case '.':
            return 4;
            break;
        case 'E':
            return 5;
            break;
        case 'e':
            return 6;
            break;
        case '\'':
            return 7;
            break;
        case '"':
            return 8;
            break;
        case '+':
            return 9;
            break;
        case '-':
            return 10;
            break;
        case '/':
            return 11;
            break;
        case '#':
            return 12;
            break;
        case '*':
            return 13;
            break;
        case '%':
            return 14;
            break;
        case '&':
            return 15;
            break;
        case '|':
            return 16;
            break;
        case '!':
            return 17;
            break;
        case '=':
            return 18;
            break;
        case '>':
            return 19;
            break;
        case '<':
            return 20;
            break;
        case '{':
            return 21;
            break;
        case '}':
            return 22;
            break;
        case '[':
            return 23;
            break;
        case ']':
            return 24;
            break;
        case '(':
            return 25;
            break;
        case ')':
            return 26;
            break;
        case ',':
            return 27;
            break;
        case ';':
            return 28;
            break;
        case '\n':
            return 30;
            break;
        case '\t':
            return 31;
            break;
        case '\b':
            return 32;
            break;
        default:
            return 29;
            break;
    }
}

void Token(int e, string c, int i, int f){
    if(i==f){
        f++;
    }

    bool flag=false;
    switch(e){
        case 100:
            pal= c.substr(i, f-i);
            for(int j=0;j<17;j++){
                if(pal==reservadas[j]){
                    flag=true;
                }
            }
            if(flag== true){
                cadToken = cadToken+c.substr(i, f-i);
                cadToken=cadToken+"  >>Palabra reservada\n";
                break;
            }else{
                cadToken = cadToken+c.substr(i, f-i);
                cadToken=cadToken+"  >>Identificador\n";
                break;
            }

        case 101:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Identificador\n";
            break;
        case 102:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Entero\n";
            break;
        case 103:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Reales\n";
            break;
        case 104:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Notación cientifica\n";
            break;
        case 105:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Suma\n";
            break;
        case 106:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Resta\n";
            break;
        case 107:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Multiplicación\n";
            break;
        case 108:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>División\n";
            break;
        case 109:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Asignación\n";
            break;
        case 110:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Igual\n";
            break;
        case 111:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Menor\n";
            break;
        case 112:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Menor igual\n";
            break;
        case 113:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Mayor\n";
            break;
        case 114:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Mayor igual\n";
            break;
        case 115:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Diferente\n";
            break;
        case 116:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Not\n";
            break;
        case 117:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>And\n";
            break;
        case 118:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Or\n";
            break;
        case 119:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Parentesis que abre\n";
            break;
        case 120:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Parentesis que cierra\n";
            break;
        case 121:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Corchete que abre\n";
            break;
        case 122:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Corchete que cierra\n";
            break;
        case 123:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Punto y coma\n";
            break;
        case 124:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Coma\n";
            break;
        case 125:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Cte caracter\n";
            break;
        case 126:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Cte String\n";
            break;
        case 127:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Comentario de linea\n";
            break;
        case 128:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Modulo\n";
            break;
        case 129:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Llave que abre\n";
            break;
        case 130:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Llave que cierra\n";
            break;

    }
}

void PosError(int e, string c, int i, int f){
    if(i==f){
        f++;
    }
    switch(e){
        case 500:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 500>>Se esperaba un digito después del punto\n";
            break;
        case 501:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 501>>Se esperaba un digito despues del exponente\n";
            break;
        case 502:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 502>>Se esperaba un digito después del signo\n";
            break;
        case 503:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 503>>Se esperaba un & después del signo &\n";
            break;
        case 504:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 504>>Se esperaba un | después del signo |\n";
            break;
        case 505:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 505>>Se esperaba un caracter entre las comillas simples\n";
            break;
        case 506:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 506>>No se esperaban valores después del delimitador\n";
            break;
        case 507:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+" <<Error 507>>Se esperaba una comilla simple que cierre\n";
            break;

    }
}

void Analizar(QString cadena){
    inicio=0;
    final=0;
    cadToken="";
    cadError="";
    std::string cad=cadena.toStdString();
    int longi=cad.length();
    for(int x=0; x<longi+1;x++){
        car=cad[x];
        rel=relaciona(car);
        edo=matriz[edo][rel];
        final=x;
        if (edo>=100 && edo<=130){
            Token(edo,cad,inicio,final);
            inicio=final+1;
            edo=0;

        }else if (edo>=500 && edo<=507){
            PosError(edo,cad,inicio,final);
            inicio=final+1;
            edo=0;
        }

    }

}


Analizador::Analizador(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Analizador)
{
    ui->setupUi(this);
}

Analizador::~Analizador()
{
    delete ui;
}

void Analizador::on_btnAbrir_clicked()
{
    QFile arch;
    QTextStream io;
    QString nombre;
    nombre = QFileDialog::getOpenFileName(this, "Abrir");
    arch.setFileName(nombre);
    arch.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!arch.isOpen()){
        QMessageBox::critical(this,"Error",arch.errorString());
        return;
    }
    io.setDevice(&arch);
    ui->txtTexto->setPlainText(io.readAll());
    arch.flush();
    arch.close();
}


void Analizador::on_btnGuardar_clicked()
{
    QFile arch;
    QTextStream io;
    QString nombre;
    nombre = QFileDialog::getSaveFileName(this, "Guardar");
    arch.setFileName(nombre);
    arch.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!arch.isOpen()){
        QMessageBox::critical(this,"Error",arch.errorString());
        return;
    }
    io.setDevice(&arch);
    io << ui->txtTexto->toPlainText();
    arch.close();
}


void Analizador::on_btnLimpiar_clicked()
{
    ui->txtTexto->setPlainText("");
    ui->txtToken->setPlainText("");
    ui->txtErrores->setPlainText("");
}


void Analizador::on_btnAnalizar_clicked()
{
    if(ui->txtTexto->toPlainText().isEmpty()){
        QMessageBox::critical(this,"Error","No hay texto que analizar");
        return;
    }else{
        QString a=ui->txtTexto->toPlainText();
        Analizar(a);
        ui->txtToken->setPlainText(QString::fromStdString(cadToken));
        ui->txtErrores->setPlainText(QString::fromStdString(cadError));
    }
}


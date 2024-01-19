#include "Validacion.h"

string Validacion::texto(string cadena, int i)
{
    string t = "";
    t = cadena[i];
    t += cadena[i + 1];
    t += cadena[i + 2];
    t += cadena[i + 3];
    return t;
}

string Validacion::textoCos(string cadena, int i)
{
    string t = "";
    t = cadena[i - 2];
    t += cadena[i - 1];
    t += cadena[i];
    t += cadena[i + 1];
    
    return t;
}

bool Validacion::esOperador(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '%':
    case '(':
        return true;
        break;
    default:
        return false;
    }
}

bool Validacion::validarAnterior(string cadena, int i)
{
    char c;
    bool vd =false;

    if (i == 0)
    {
        vd = true;
    }
    c = cadena[i - 1];
    if (esOperador(c))
    {
        vd = true;
    }
    return vd;
}

bool Validacion::validar_Sen(string cadena)
{
    string sin = "sin(";
    string cos = "";
    string sqr = "sqrt(";
    string cadenita = "";
    bool sen = true;
    bool sqt = true;
    bool cc = false;
    bool valS;
    for (int i = 0; i < cadena.size(); i++)
    {
        if (cadena[i] == 115)
        {
            valS = this->validarAnterior(cadena, i);
            cadenita = this->texto(cadena, i);
            if (cadena[i + 1] == 105 && valS)
            {
                if (sin == cadenita)
                {
                    sen = true;
                }
                else
                {
                    sen = false;
                }
            }

            else if (cadena[i + 1] == 113 && valS)
            {
                cadenita += cadena[i + 4];
                if (sqr == cadenita)
                {
                    sqt = true;
                }
                else
                {
                    sqt = false;
                }
            }

            else
            {
                cos = this->textoCos(cadena, i);
                if (cos == "cos(")
                {
                    sen = true;
                }
                else
                {
                    sen = false;
                }
            }
        }
    }
    if (sen && sqt)
    {
        cc = true;
    }
    else
    {
        cc = false;
    }
    return cc;
}

bool Validacion::validar_Cos(string cadena)
{
    string cos = "cos(";
    string cadenita = "";
    int count = 0;
    bool val = false;
    bool c;
    for (int i = 0; i < cadena.size(); i++)
    {
        if (cadena[i] == 99)
        {
            count++;
            c = this->validarAnterior(cadena, i);
            cadenita = this->texto(cadena, i);
            if (cos == cadenita && c)
            {
                val = true;
            }
            else
            {
                val = false;
            }
        }
        else if (count == 0)
        {
            val = true;
        }
    }
    return val;
}

bool Validacion::validar_Tan(string cadena)
{
    string tan = "tan(";
    string cadenita = "";
    bool val = true;
    bool v_DT;
    for (int i = 0; i < cadena.size(); i++)
    {
        if (cadena[i] == 116 && cadena[i + 1] == 97)
        {
            v_DT = this->validarAnterior(cadena, i);
            cadenita = this->texto(cadena, i);
            if (tan == cadenita && v_DT)
            {
                val = true;
            }
            else
            {
                val = false;
            }
        }
    }
    return val;
}

bool Validacion::vaidar_Escritura(string cadena)
{
    bool valid = false;
    bool seno = this->validar_Sen(cadena);
    bool coseno = this->validar_Cos(cadena);
    bool pi = this->validar_Pi(cadena);
    bool tan = this->validar_Tan(cadena);
    if (this->validar_Cos(cadena) && this->validar_Sen(cadena) && this->validar_Tan(cadena) && this->validar_Pi(cadena))
    {
        valid = true;
    }
    return valid;
}

bool Validacion::validar_Pi(string cadena)
{
    string pi = "pi";
    string cadenita = "";
    bool v_pi = true;
    bool v_D;
    for (int i = 0; i < cadena.size(); i++)
    {
        if (cadena[i] == 112)
        {
            v_D = this->validarAnterior(cadena, i);
            cadenita = cadena[i];
            cadenita += cadena[i + 1];
            if (pi == cadenita && v_D)
            {
                v_pi = true;
            }
            else
            {
                v_pi = false;
            }
        }
    }
    return v_pi;
}

bool Validacion::Parentesis_Balanceados(string cadena) {
    int iz = 0;
    int der = 0;
    for (int i = 0; i < cadena.size(); i++)
    {
        if (cadena[i] == '(')
        {
            iz++;
        }
        else if (cadena[i] == ')')
        {
            der++;
        }
    }
    iz = iz - der;
    if (iz == 0)
    {
        return true;
    }
    else
        return false;
}



bool Validacion::Parentesis_Sintaxis(string cadena) {
    int n = 0;
    if (this->Parentesis_Balanceados(cadena))
    {
        for (int i = 0; i < cadena.size(); i++)
        {
            if (cadena[i] == ')')
            {
                if (esOperador(cadena[i - 1]))
                {
                    n++;
                    cout << "Verificar )" << endl;
                    break;
                }
                else {
                    continue;
                }
            }
            else if (cadena[i] == '(') {
                if (esOperador(cadena[i + 1]) || cadena[i - 1] == ')')
                {
                    n++;
                    cout << "Verificar (" << endl;
                    break;
                }
                else {
                    continue;
                }
            }

        }
        if (n == 0)
        {
            return true;
        }
        else
            return false;
    }
    else {
        return false;
    }
}

bool Validacion::Operadores_Sintaxis(string cadena)
{
    bool v = true;
    for (int i = 0; i < cadena.size(); i++)
    {
        if (esOperador(cadena[i]) && cadena[i] != ')' && cadena[i] != '(')
        {
            if (esOperador(cadena[i + 1]) && cadena[i+1] != ')' && cadena[i+1] != '(')
            {
                v = false;
                break;
            }
        }

    }
    return v;
}
bool Validacion :: validar_Ceros(string cadena)
{
    bool cero=true;
    for (int i = 0; i < cadena.size(); i++)
    {
        if (cadena[i]=='/'&& cadena[i+1]=='0')
        {
            cero=false;
        }
    }
    return cero;
}
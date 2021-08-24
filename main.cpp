#include <iostream>

using namespace std;

#define MAX_STRING 1024

int main()
{
    FILE *fp;

    cout << "Divisor de mensajes" << endl;

    cout << "Ingrese archivo a dividir (filepath): ";

    char file[MAX_STRING];

    cin >> file;

    fp = fopen(file, "r");

    if(fp == NULL)
    {
        cout << "Error abriendo el arhivo " << file << endl;
		system("pause");
        return -1;
    }

    char *buf = new char[MAX_STRING];
    int msg = 0;

    while(fgets(buf, MAX_STRING, fp) != 0)
    {
        if(buf[0] == '2' && buf[1] == '0' && buf[2] == '2' && buf[3] == '1')
            msg++;
    }

    int division;

    cout << "El archivo contiene " << msg << " mensajes" << endl;
    cout << "Ingrese de cuantos mensajes deben ser las mediciones: ";

    cin >> division;

    cout << "Se crearan " << (msg / division) + (msg % division != 0 ? 1 : 0) << " divisiones" << endl;

    cout << "Desea continuar?(Y/n)" << endl;

    char c;

    cin >> c;

    if(c != 'Y' && c != 'y')
    {
        cout << "Se cerrara el programa" << endl;

        delete [] buf;

        fclose(fp);
		
		system("pause");

        return 0;
    }


    cout << "Dividiendo en partes de " << division << " mensajes cada una" << endl;

    fseek(fp, 0, SEEK_SET);

    int file_n = 0;

    while(1)
    {

        cout << "Division " << file_n << " de " << (msg / division) + (msg % division != 0 ? 1 : 0) << endl;

        char file_div[] = "div(XXX).txt";

        file_div[4] = (file_n / 100) + 0x30;
        file_div[5] = ((file_n % 100) / 10) + 0x30;
        file_div[6] = (file_n % 10) + 0x30;

        FILE *div = fopen(file_div, "w+");
		
		if(div == NULL)
		{
			cout << "Error creando division" << endl;
		}

        int current_msg = 0;

        int r = 1;

        while(1)
        {
            long ft = ftell(fp);

            if(fgets(buf, MAX_STRING, fp) == 0)
            {
                r = 0;
                break;
            }

            if(buf[0] == '2' && buf[1] == '0' && buf[2] == '2' && buf[3] == '1')
                current_msg++;

            if(current_msg <= division)
            {
                fputs(buf, div);
            }
            else
            {
                fseek(fp, ft, SEEK_SET);
                break;
            }
        }

        fclose(div);

        file_n++;

        if(r != 1)
            break;
    }

    delete [] buf;

    fclose(fp);
	
	system("pause");

    return 0;
}

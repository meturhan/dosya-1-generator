#include "stdafx.h"
#include "stdio.h"
#include <fstream> // dosya i�lemleri
#include <iostream> // giri� ��k��
#include <string>	// string i�lemleri
#include <sstream> // stringi inte ve inti stringe �evirme i�lemleri..

using namespace std;

void ListeyeEkle(string str); // okunan kay�tlar� form matrisine yazar..
int LEIndex=0; // form matrisinde kal�nan yeri tutar..

int kayitAlaniHesapla(); // bir kay�t i�in gereken alan� hesaplar..

string stringUret(int min,int max,string formatSpec); // random string �retici..

int random(int min,int max);// random say� �retici

void dosyayaYaz(string data_file,int kacKayit,int kayitAlani);

string form[20][5]; // okunan kay�tlar� tutacak matris yap�s�..

void main(int argc, char* argv[])
{
	string kacKayitBuff = argv[3];
	int kacKayit;
	istringstream buff(kacKayitBuff);
	buff>>kacKayit;
	string format_file = argv[1],data_file=argv[2];
	int kayitAlani; // bir kay�t i�in gereken alan� tutacak..
	cout<<"Program Basi..! |"<<endl<<"----------------"<<endl;
	string str; // format_file dosyas�ndan sat�rlar� okuyacak..
	
	//-------------------------------------

	ifstream gDosya(format_file.c_str()); // Format dosyas� a��l�yor..
	
	while(gDosya>>str)//S�rayla sat�rlar okunuyor..
	{
		ListeyeEkle(str);//form matrisine d�zenli olarak ekleniyor..
	}
	kayitAlani = kayitAlaniHesapla();
	cout<<endl<<" - Bilgiler hafizaya basariyla alindi..."<<endl;
	cout<<" - Her bir kayit icin gereken alan : "<<kayitAlani<<" Byte'tir."<<endl;
	cout<<" - Toplam "<<LEIndex<<" field vardir.."<<endl;

	cout<<" - Kayitlar dosyaya yaziliyor..."<< endl;
	dosyayaYaz(data_file.c_str(),kacKayit,kayitAlani);
	cout<<" - Kayitlar dosyaya basariyla yazildi....."<< endl;
	
	//-------------------------------------
	cout<<endl<<"----------------"<<endl<<"Program Sonu..! |";
}

void ListeyeEkle(string str) //okunan kay�tlar� form matrisine yazar..
{ 
	try
	{
		cout<<endl<<"\"  "<<str<<"  \"  "<<"satiri hafizaya aliniyor..."<<endl<<endl; 
		form[LEIndex][0].assign(str,0,str.find(',')); //str = Gamer,String,10,4-6,"******"
		str = str.substr(str.find(',')+1);//str = String,10,4-6,"******"
		form[LEIndex][1].assign(str,0,str.find(','));
		str = str.substr(str.find(',')+1);//str = 10,4-6,"******"
		form[LEIndex][2].assign(str,0,str.find(','));
		str = str.substr(str.find(',')+1);//str = 4-6,"******"
		
		if(str.find('-')!= -1) // '-' karakteri varsa random range alan�na yaz�lacak.. (�rnek i�in var)
		{
			form[LEIndex][3].assign(str,0,str.find(','));
			str = str.substr(str.find(',')+1);// str = "******"
		}
		else // '-' karakteri yoksa random range alan�na y-o-k yaz�lacak..
		{
			form[LEIndex][3]="y-o-k";
		}

		if(str.find('"') != -1) // '"' karakteri varsa format spec. alan�na yaz�lacak.. (�rnek i�in var)
		{
			form[LEIndex][4].assign(str);
		}
		else // '"' karakteri yoksa format spec alan�na y-o-k yaz�lacak..
		{
			form[LEIndex][4] = "y-o-k";
		}

		//ekrandan kontrol i�in..
		cout<<"   Name		   : "<<form[LEIndex][0]<<endl;
		cout<<"   Type		   : "<<form[LEIndex][1]<<endl;
		cout<<"   Size		   : "<<form[LEIndex][2]<<" Bytes "<<endl;
		if(form[LEIndex][3] != "y-o-k")
		{
			cout<<"   Random Range	   : "<<form[LEIndex][3]<<endl;
		}
		if(form[LEIndex][4] != "y-o-k")
		{
			cout<<"   Format Spec.	   : "<<form[LEIndex][4]<<endl;
		}

		//matriste bir alt sat�ra ge�elim..
		LEIndex++;
	}
	catch(string hata)
	{
		cout<<"Format dosyasi hafizaya alinamadi..!"<<endl<<hata<<endl;
	}
}

int kayitAlaniHesapla()
{
	int satirSayisi = LEIndex-1;
	int sayac = 0;
	int kayitAlani=0;
	
	while(sayac<=satirSayisi)
	{
		istringstream buffer(form[sayac][2]);//
		int ara;                            // str2int i�lemi...
		buffer>>ara;                       //
		kayitAlani += ara;
		sayac++;
	}
	return kayitAlani;
}
string stringUret(int min,int max,string formatSpec)
{
	string randStr=""; // �retilen string
	int karakterSayisi = 0; // �retilen stringin karakter say�s�
	karakterSayisi = random(min,max); // normal ise random bi de�er al�yor..

	char c; // yaz�lacak karakter..
	int sayici=0; // ge�ici say�c�

	if(formatSpec.length()>3) // spec. varsa k�rpmaya..
	{
		formatSpec = formatSpec.substr(1,formatSpec.length()-2); // "" i�aretleri yok ediliyor..
	}
	

	//randomize...
	
	while(sayici<karakterSayisi)
	{
		if(sayici<formatSpec.length()) // format spec. tan�mlanm��sa o byte i�in
		{
			if(formatSpec[sayici] == '*')
			{
				c = rand()%3;
				if(c==0)
				{
					c = random(48,57);//0-9
				}
				if(c==1)
				{
					c = random(65,90);//A-Z
				}
				if(c==2)
				{
					c = random(97,122);//a-z
				}
			}
			else if(formatSpec[sayici] == '#')
			{
				c = random(48,57); //0-9
			}
			else if((formatSpec[sayici]>0) && (formatSpec[sayici]<=255))
			{
				c = formatSpec[sayici]; // sabit..
			}
			else
			{
				c = rand()%255; // herhangi bir ascii
			}
		}
		else
		{
			c = rand()%255;
		}
		randStr+=c; // s�raya ekle
		sayici++;
	}
	
	return randStr; // random �retilen string..
}

int random(int min,int max) // aral�k i�inde random say�..
{
	int sayi=(rand()*rand())%(max+1);
	while(sayi<min)
	{
		sayi = rand()%(max+1);
	}
	return sayi;
}
void dosyayaYaz(string data_file,int kacKayit,int kayitAlani)
{	
	int i=0; // field say�c�
	FILE *d = fopen(data_file.c_str(),"w"); // data_file a��l�yor
	int atlama=0;//ka�ar byte atlanaca��n� tutar
	for(i=0;i<LEIndex;i++) // herbir field i�in
	{			
		string formatSpec; // format specification tutar
		string type;  // tip bilgisini tutar
		string rangeBuffer; // aral�k bilgisi �rn. 4-6 �eklinde gelince daha sonra ay�rmak i�in ge�ici olarak tutar..
		string randStr; // random �retti�imiz stringleri tutar..
		int randInt; // random �retti�imiz integerlar� tutar..
		char bosluk = ' '; // bo�luk karakteri..
		int size,minRange,maxRange; // boyut,minimum,ve maksimum de�erlerini tutar..(varsa)
		
		

		type = form[i][1]; // tip bilgisi string olarak al�n�yor
		istringstream buffer(form[i][2]); // boyut bilgisi string olarak al�n�yor ve integer'a �evirmek i�in buffer de�i�kenine al�n�yor
		buffer>>size; // boyut bilgisi tamsay� tipine �evriliyor
		rangeBuffer = form[i][3]; // aral�k bilgisi string olarak al�n�yor
		formatSpec = form[i][4]; // format spec. bilgisi string olarak al�n�yor
		
		if(formatSpec == "y-o-k") // daha �nce format spec. i�ine y-o-k yerle�tirdiysek bo� olarak al�yoruz.
		{
			formatSpec = "";
		}

		if(rangeBuffer != "y-o-k") // range buffer da �yle..
		{
			istringstream buffer2(rangeBuffer.substr(rangeBuffer.find('-')+1)); // str2int i�lemleri..(- i�aretinden kurtarmada burada..)
			buffer2>>maxRange;
			istringstream buffer3(rangeBuffer.substr(0,rangeBuffer.find('-')));
			buffer3>>minRange;
		}
		else
		{
			minRange = maxRange = size; // e�er s�n�rlama yoksa tek s�n�r�m�z boyut oluyor..
		}

		if(type == "String") // string tipindeyse..
		{
			int i_1; // yaz�lacak kay�tlar� sayar..
			int i_2; // stringin s�rayla karakterlerini sayar..
			
			for(i_1=0;i_1<kacKayit;i_1++)
			{			
				randStr = stringUret(minRange,maxRange,formatSpec); // random string..
				fseek(d,(i_1*kayitAlani) + atlama,SEEK_SET);
				
				/*burada yap�lan i�lem ��yledir : �rne�in 5. kayd� yaz�yor olal�m 
				  (i_1 = 5) kay�t alan� �rnek format dosyas�nda 25'tir.Yine bu dosyadaki 
				   tarih bilgisini yaz�yor olal�m.. Yazmaya ba�lanacak byte (5*25)+15 byte'� 
				   olacakt�r.atlama de�i�keni yaz�lm�� fieldlar�n toplam boyutunu tutar..*/

				for(i_2=0;i_2<randStr.length();i_2++) // stringi byte byte yaz..
				{
					fwrite(&randStr[i_2],sizeof(char),1,d);
				}
				if(i_2<size-1)// stringe ayr�lan alan tam dolmad�ysa bo�luk karakteriyle doldur..
				{
					while(i_2 <= size-1)
					{
						fwrite(&bosluk,sizeof(char),1,d);
						i_2++;
					}
				}
			}			
		}
		else if(type == "Integer") // integer tipinde ise
		{
			int i_1;
			int i_2;
			//kay�tlar direk integer olarak yaz�l�yor..5 byte l�k alan istendi�inden ilk byte bo�luk yaz�l�r.
			for(i_1=0;i_1<kacKayit;i_1++)
			{			
				randInt = random(minRange,maxRange);
				fseek(d,(i_1*kayitAlani) + atlama,SEEK_SET);
				
				for(i_2=0;i_2<(size-sizeof(int));i_2++) // integer i�in fazladan alan istenmi�se fazla olanlar bo�luk ile dolduruluyor..
				{
					fwrite(&bosluk,sizeof(char),1,d);
				}
				fwrite(&randInt,sizeof(int),1,d); // tamsay� yaz�l�yor..
			}			
		}
		atlama+=size;
	}//for sonu--
	
	fclose(d);	
}


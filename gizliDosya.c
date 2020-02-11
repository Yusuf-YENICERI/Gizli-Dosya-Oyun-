#include<conio.h>//kbhit() fonksiyonu i�in
#include<stdio.h>
#include<windows.h>//system() fonksiyonuyla "cls" ve "color" komutlar� i�in
#include<stdlib.h>//srand()(rastgele de�er alma) fonksiyonu i�in
#include<time.h>//time(NULL) fonksiyonu i�in. srand() fonksiyonundan rastgele de�er almak i�in zaman kullan�l�yor.
int konumX = 9, konumY = 0, puan = 0, beceremedi = 0, oyunaDevam = 1, say = 0 /*say de�i�keniyle haritaya ka� tane dosya koydu�unu saymak ve max puan� ona g�re belirlemek i�in, puan de�i�keni mevcut puan� g�r�nt�lemek i�in, oyunaDevam, oyuna devam edilip edilmeyece�ini belirlemek i�in, beceremedi, oyunu kazan�p kazanmad���n� belirlemek i�in, konumX, 'A' karakterinin mevcut sat�r�n� temsil eder, konumY, 'A' karakterinin mevcut s�tununu temsil eder.*/;
int guvenlik[4][2] = { 2,15, 3,62, 5,40, 7,78 }; //4 g�venlik eleman�n�n s�ras�yla sat�r ve sutun de�erleri tutulmaktad�r. konumX ve konumY de�i�kenleriyle ayn� mant��a sahiptir.
char screen[10][103] = { " |  |                        |                                                          |-------|     \n",
" |  |--     ----------------  -------------     |       |------------                  |       |      \n",
" |  |          G|      |                  |     |       |      |    |          |--------       |      \n",
"    -------------      |                  |     --------|     G|    |    |------       |---    |      \n",
"                       |      --------|   |             |           |    |         |   |       |      \n",
" |  --------------     |      |       | G |  ---|--------           |    |     |   |   |---    |      \n",
" |  |            |     |      |       |   |     |              |    |-  --     --------|       |      \n",
" |  |    |   |   |                    |   |     |   -----------|              G|       |       |      \n",
" |  |    |   ----|     |---------------   |------   |               |-----     |       |       |      \n",
"A|  |-----             |              |             |               |                          cikis\n", };//screen dizisi haritay� tutmaktad�r.

//Oyunu ba�latmak i�in
void oyunuBaslat();

//Gizli dosyalar� koymak i�in say� d�nd�r
void dosyalariKoy();

//Yukar� tu�una bas�nca karakter hareketi
void yukariHareket();

//Asagi tusuna basinca karakter hareketi
void asagiHareket();

//Sag tusuna basinca karakter hareketi
void sagaHareket();

//Sola tusuna basinca karakter hareketi
void solaHareket();

//Program� bekletmek i�in
void beklet(int);

//g�venlik g�revlilerinin hareket etmesi i�in
void guvenlikHareket();

//g�venlik g�revli yukar� hareket, parametre hangi g�venlik g�revlisi oldu�unu belirlemek i�in
void yukariHareketGuvenlik(int);

//g�venlik g�revli a�a�� hareket, parametre hangi g�venlik g�revlisi oldu�unu belirlemek i�in
void asagiHareketGuvenlik(int);

//g�venlik g�revli sola hareket, parametre hangi g�venlik g�revlisi oldu�unu belirlemek i�in
void solaHareketGuvenlik(int);

//g�venlik g�revli sa�a hareket, parametre hangi g�venlik g�revlisi oldu�unu belirlemek i�in
void sagaHareketGuvenlik(int);

int main(void)
{
	//Rastgele say�lar almak i�in zaman vas�tas�yla seed et
	srand(time(NULL));

	//oyunu ba�lat
	oyunuBaslat();

	return 0;
}

void oyunuBaslat() {

	int hemenBitir = 0;

	//�nce gizli dosyalar� koy
	dosyalariKoy();

	//giri� ve biti� c�mleleri i�in 2 boyutlu dizi tan�mla.(5 c�mle her biri 1000 karaktere sahip)
	char giris2[8][1000] = { "Ajan Rex'in acilen tum gizli dosyalari guvenlik gorevlilerine yakalanmadan toplamasi lazim.","\nOnlar","\nGELIYORLAR!!!","\nDosyalari toplamak icin hemen bir tusa BAS!","Ajan Rex dosyalari basariyla topladi. \nSiradaki gorev onu bekliyor...","AJAN REX BASARISIZ OLDU, YENI AJANLAR GOREVI DEVRALACAK...","Oyun icerisinde:\nA - Ajan Rex'i temsil eder.\nG - Guvenlik gorevlilerini temsil eder.\n* - Gizli dosyalari temsil eder.\n\nOyun icerisinde yapilabilecek seyler sunlardir:\n1 - En alt satirdan en ust satira gecilebilir.\n2 - En ust satirdan en alt satira gecilebilir.\n\nOyun nasil sona erer?\nAjan Rex ne zaman tum dosyalari toplayip \"cikis\" yazisina giderse!(Acil cikis icin Esc tusuna basabilirsin)\n\nIyi oyunlar :D","Oyuna baslamak icin herhangi bir tusa tikla..." };

	//ilk c�mleye i�aretciyle i�aret et(asl�nda c�mlenin ilk karakterine i�aret ediyor.).
	char *giris = giris2[0];
	
	//Arka plan� siyah, �n plan� ye�il yap.
	system("color 0a");
	
	//d�ng� i�in de�i�ken olu�tur.
	int don;
	//d�ng� yard�m�yla ekrana karakterleri bir bir bekleterek yazd�r.
	for (don = 0;; don++)
	{
		//E�er dizimizin karakteri '\0' ise o zaman c�mle sonuna geldik, d�ng�den ��k. E�er dizimizin karakteri '\0' de�il ise ekrana yazd�r.
		if (giris2[0][don] != '\0')
		{
			//ekrana bir karakter yazd�r
			printf("%c", giris2[0][don]);

			//program� beklet
			beklet(40);
		}
		else
			break;
	}


	//Ekrana c�mleyi yazd�rd�ktan sonra program� biraz daha uyut.
	beklet(2000);

	//Ekrana dizinin 2. ci c�mlesini(1+1=2) yazd�r.
	printf("%s", giris2[1]);

	//Ekrana c�mleyi yazd�rd�ktan sonra program� biraz daha uyut.
	beklet(2000);

	//Ekrana dizinin 3. c� c�mlesini(2+1=3) yazd�r.
	printf("%s", giris2[2]);

	//Ekrana c�mleyi yazd�rd�ktan sonra program� biraz daha uyut.
	beklet(3000);

	//Oyunla ilgili bilgileri yazd�rmak i�in, ekran� temizle.
	system("cls");

	//Arka plan� beyaz, �n plan� k�rm�z� yap.
	system("color f4");

	//Ekrana oyunla ilgili bilgileri yazd�r.
	printf("%s\n", giris2[6]);

	//Program� beklet
	beklet(1000);

	//Ekrana dizinin 8. ci c�mlesini(7+1=8) yazd�r.
	printf("%s", giris2[7]);
	
	//Devam etmek i�in herhangi bir tu�a bas k�sm�nda ba��lan tu�u yakalay�p buffer�(bilgisayarda giri� yapt���m�z(mesela klavyeden yazd���m�z �eyler) �eylerin depoland��� k���k birim) temizle. While d�ng�s� kullan�lmas�n�n sebebi herhangi bir inputu beklemek 
	while (1)
	{
		//Herhangi bir tu�a bas�l�p bas�lmad���n� yakalamak i�in
		if (kbhit())
		{
			//buffer�(bilgisayarda giri� yapt���m�z(mesela klavyeden yazd���m�z �eyler) �eylerin depoland��� k���k birim) temizlemek i�in girilen karakteri al
			getch();

			//d�ng�den ��k
			break;
		}
	}
	//Arka plan� ye�il, �n plan� sar� yap.
	system("color 2e");
	//oyunun as�l k�sm�, bu k�s�mda ekran yazd�r�l�yor. oyunaDevam ile oyuncunun ��k��a ula��p ula�mad���, herhangi bir g�venlik g�revlisine yakalan�p yakalanmad��� kontrol ediliyor.
	while (oyunaDevam)
	{

		//getch ile tu� de�erlerini almak i�in
		int take = 0;

		//her i�lemden sonra ekran� temizlemek i�in
		system("cls");

		//g�venli�i hareket ettir
		guvenlikHareket();

		//Ekrana g�ncel paun�n yazd�r�ld��� k�s�m, screen = harita, puan = mevcut puan, (say*10 - puan ) = ��kabilmek i�in kalan dosya say�s�,  say * 10 = Max Puan
		printf("%s\n\nPuanin : %d%sCikabilmek icin kalan dosya sayisi : %d%sMax Puan : %d", screen, puan, "                 ", (say * 10 - puan) / 10, "                   ", say * 10);

		//Program� biraz uyut ki ekran devaml� gidip gelmesin
		beklet(40);

		//tu�a bas�l�p bas�lmad���n� tespit etmek i�in
		if (kbhit())
		{
			//Ok tu�lar� 224-72 gibi de�er d�nd�r�r. �nce 224 de�erini for d�ng�s�yle al�yorum.
			for (; take != 224;)
			{
				//224 ya da Esc tu�una bas�ld�ysa sadece 27 de�erini almak i�in.
				take = getch();
				
				//E�er ESC tu�una bas�ld�ysa oyunaDevam � 0 a ayarla ki oyun bitsin. Ayr�ca hemenBitir de�i�kenini 1 e ayarlaki oyun hemenBitsin(Ekrana herhangi bir �ey yazmadan)
				if (take == 27)
				{
					oyunaDevam = 0;
					hemenBitir = 1;
					//ve d�ng�den ��k
					break;
				}
			}
			
			//hemenBitir 0 ise oyun hemen bitmiyor ancak 1 ise hemen bitiyor.
			if (!hemenBitir)
			{

				//Sonras�nda '-' karakterini al�yorum.
				take = getch();
				//En son olarak ula�mak istedi�im de�ere switch case yap�s�yla ula��yorum.
				switch (take)
				{
					//yukar� tusu
				case 72:
					yukariHareket();
					break;
					//a�a�� tu�u
				case 80:
					asagiHareket();
					break;
					//sol tu�u
				case 75:
					solaHareket();
					break;
					//sa� tu�u
				case 77:
					sagaHareket();
					break;
				}

			}
		}

	}

	//hemenBitir 0 ise oyun hemen bitmiyor ancak 1 ise hemen bitiyor.
	if (!hemenBitir)
	{
		//oyunu kazan�p kazanmad���n� beceremedi de�i�keniyle kontrol ediyoruz.
		if (!beceremedi)
		{
			//Ekran� temizliyoruz ki oyun ekran� temizlensin ve verilmesi gereken mesaj verilsin.
			system("cls");
			
			//Arka plan� beyaz, �n plan� ye�il yap.
			system("color f2");
			
			//d�ng� yard�m�yla ekrana karakterleri bir bir bekleterek yazd�r.
			for (don = 0;; don++)
			{
				//E�er dizimizin karakteri '\0' ise o zaman c�mle sonuna geldik, d�ng�den ��k. E�er dizimizin karakteri '\0' de�il ise ekrana yazd�r.
				if (giris2[4][don] != '\0')
				{
					//ekrana bir karakter yazd�r
					printf("%c", giris2[4][don]);
		
					//program� beklet
					beklet(40);
				}
				else
					break;
			}
		}
		else
		{
			//Ekran� temizliyoruz ki oyun ekran� gitsin ve verilmesi gereken mesaj verilsin.
			system("cls");
			
			//Arka plan� beyaz, �n plan� k�rm�z� yap.
			system("color fc");
			//d�ng� yard�m�yla ekrana karakterleri bir bir bekleterek yazd�r.
			for (don = 0;; don++)
			{
				//E�er dizimizin karakteri '\0' ise o zaman c�mle sonuna geldik, d�ng�den ��k. E�er dizimizin karakteri '\0' de�il ise ekrana yazd�r.
				if (giris2[5][don] != '\0')
				{
					//ekrana bir karakter yazd�r
					printf("%c", giris2[5][don]);
		
					//program� beklet
					beklet(40);
				}
				else
					break;
			}

		}

		//program� uyut(belli bir s�re beklesin ondan sonra oyundan ��ks�n)
		beklet(2500);

	}
}


//gizli dosyalar� haritaya yerle�tirmek i�in
void dosyalariKoy()
{
	//dosya konumu belirlemek i�in 2 elemana sahip belirle dizisini olu�tur, d�ng�ler i�in i ve j de�i�kenini olu�tur
	int belirle[2], i, j;

	//d�ng�y� 20 kez d�nd�rerek haritada bo� olan yerlere dosyalar�(*) koy 
	for (i = 0; i<20; i++)
	{
		//belirle dizisinin ilk eleman�n� haritada 2 boyutlu dizinin ilk belirteci(screen[10][101]) olarak kullan, rand() fonksiyonuyla rastgele say� al ve %10 ile haritan�n sutun say�s�na g�re rastgele say�n�n modunu al(screen[sutun][sat�r] dizisinin sutun k�sm�)
		belirle[0] = rand() % 10;

		//belirle dizisinin 2.eleman�n� haritada 2 boyutlu dizinin 2.ci belirteci(screen[10][101]) olarak kullan, rand() fonksiyonuyla rastgele say� al ve %95 ile haritan�n sat�r say�s�na g�re rastgele say�n�n modunu al(screen[sutun][sat�r] dizisinin sat�r k�sm�)
		belirle[1] = rand() % 95;

		//haritan�n bo� yeri mi diye kontrol et
		if (screen[belirle[0]][belirle[1]] == ' ')
		{
			//dosyay� koy('*' kullanarak)
			screen[belirle[0]][belirle[1]] = '*';

			//say de�i�kenini her dosya koyduktan sonra artt�r.
			say++;
		}
	}



}

//yukar� tu�una bas�l�nca yukar� hareket et
void yukariHareket()
{
	//konumX screen dizisinin sutununu belirtir --> screen[sutun][sat�r], e�er konumX 0 ise bu durumda hareket etti�imizde(yukar� hareket i�in 1 ��karmak gerek) -1 e d��ece�iz, bunu �nlemek i�in
	if (konumX == 0)
	{
		//bulundu�umuz sat�r�n sutununu 9 a alaca��z(-1 olmas�n� istemiyoruz), bu y�zden �nce bo� mu diye kontrol et
		if (screen[9][konumY] == ' ')
		{
			//mevcut konumu temizle
			screen[konumX][konumY] = ' ';

			//sutunu 10 a g�ncelle(-1 ��kt���nda 9 a denk gelecek)
			konumX = 10;
		}
	}

	//konumX den 1 ��kararak sutun say�s�n�n azalmas�n�, b�ylece yukar� hareket etmeyi sa�la, ayn� zamanda sutun say�s�na mod al ki(%10) konumX 9 say�s�n� a�amas�n. E�er yeni konumda '*' varsa oray� temizle
	if (screen[(konumX - 1) % 10][konumY] == '*')
	{
		//yeni yeri temizle
		screen[(konumX - 1) % 10][konumY] = ' ';

		//puan� her dosya buldu�unda 10 artt�r
		puan += 10;
	}

	//konumX den 1 ��kararak sutun say�s�n�n azalmas�n�, b�ylece yukar� hareket etmeyi sa�la, ayn� zamanda sutun say�s�na mod al ki(%10) konumX 9 say�s�n� a�amas�n. E�er yeni konum bo�sa oraya karakteri koy
	if (screen[(konumX - 1) % 10][konumY] == ' ')
	{
		//mevcut konumu temizle
		screen[konumX][konumY] = ' ';

		//yeni konuma karakteri koy
		screen[(konumX - 1) % 10][konumY] = 'A';

		//konumX i g�ncelle
		konumX = (konumX - 1) % 10;
	}

	//yanmay� ayarla
	if (screen[(konumX - 1) % 10][konumY] == 'G')
	{
		oyunaDevam = 0;
		beceremedi = 1;
	}
}

//a�a�� tu�una bas�l�nca a�a�� hareket et
void asagiHareket()
{
	//konumX ile 1 i toplayarak sutun say�s�n�n artmas�n�, b�ylece a�a�� hareket etmeyi sa�la, ayn� zamanda sutun say�s�na mod al ki(%10) konumX 9 say�s�n� a�amas�n. E�er yeni konumda '*' varsa oray� temizle
	if (screen[(konumX + 1) % 10][konumY] == '*')
	{
		//yeni yeri temizle
		screen[(konumX + 1) % 10][konumY] = ' ';

		//puan� her dosya buldu�unda 10 artt�r
		puan += 10;
	}

	//konumX ile 1 i toplayarak sutun say�s�n�n artmas�n�, b�ylece yukar� hareket etmeyi sa�la, ayn� zamanda sutun say�s�na mod al ki(%10) konumX 9 say�s�n� a�amas�n. E�er yeni konum bo�sa oraya karakteri koy
	if (screen[(konumX + 1) % 10][konumY] == ' ')
	{
		//mevcut konumu temizle
		screen[konumX][konumY] = ' ';

		//yeni konuma karakteri koy
		screen[(konumX + 1) % 10][konumY] = 'A';

		//konumX i g�ncelle
		konumX = (konumX + 1) % 10;
	}

	if (screen[(konumX + 1) % 10][konumY] == 'G')
	{
		oyunaDevam = 0;
		beceremedi = 1;
	}
}


void solaHareket()
{
	//konumY den 1 i ��kararak sat�r say�s�n�n azalmas�n�, b�ylece sola hareket etmeyi sa�la, ayn� zamanda sat�r say�s�n�n gerekli olan k�sm�na(oyunun d��� '\n' hari�) mod al ki(%95) konumY 94 say�s�n� a�amas�n. E�er yeni konumda '*' varsa oray� temizle
	if (screen[konumX][(konumY - 1) % 95] == '*')
	{
		//yeni yeri temizle
		screen[konumX][(konumY - 1) % 95] = ' ';

		//puan� her dosya buldu�unda 10 artt�r
		puan += 10;
	}
	//konumY den 1 i ��kararak sat�r say�s�n�n azalmas�n�, b�ylece sola hareket etmeyi sa�la, ayn� zamanda sat�r say�s�n�n gerekli olan k�sm�na(oyunun d��� '\n' hari�) mod al ki(%95) konumY 94 say�s�n� a�amas�n. E�er yeni konumda ' ' varsa oraya ilerle ve karakteri oraya koy
	if (screen[konumX][(konumY - 1) % 95] == ' ')
	{
		//mevcut konumu temizle
		screen[konumX][konumY] = ' ';

		//yeni konuma karakteri koy
		screen[konumX][(konumY - 1) % 95] = 'A';

		//konumY i g�ncelle
		konumY = (konumY - 1) % 95;
	}

	if (screen[konumX][(konumY - 1) % 95] == 'G')
	{
		oyunaDevam = 0;
		beceremedi = 1;
	}
}

void sagaHareket()
{
	//konumY ile 1 i toplayarak sat�r say�s�n�n artmas�n�, b�ylece sa�a hareket etmeyi sa�la, ayn� zamanda sat�r say�s�n�n gerekli olan k�sm�na(oyunun d��� '\n' hari�) mod al ki(%96) konumY 95 say�s�n� a�amas�n. E�er yeni konumda '*' varsa oray� temizle
	if (screen[konumX][(konumY + 1) % 96] == '*')
	{
		//yeni yeri temizle
		screen[konumX][(konumY + 1) % 96] = ' ';

		//puan� her dosya buldu�unda 10 artt�r
		puan += 10;
	}

	//konumY ile 1 i toplayarak sat�r say�s�n�n artmas�n�, b�ylece sa�a hareket etmeyi sa�la, ayn� zamanda sat�r say�s�n�n gerekli olan k�sm�na(oyunun d��� '\n' hari�) mod al ki(%96) konumY 95 say�s�n� a�amas�n. E�er yeni konumda ' ' varsa oraya ilerle ve karakteri oraya koy
	if (screen[konumX][(konumY + 1) % 96] == ' ')
	{
		//mevcut konumu temizle
		screen[konumX][konumY] = ' ';

		//yeni konuma karakteri koy
		screen[konumX][(konumY + 1) % 96] = 'A';

		//konumY i g�ncelle
		konumY = (konumY + 1) % 95;
	}

	//mevcut paun haritaya yerle�tirilen dosya say�s�n�n 10 kat�na e�itse(10 kat� olmas�n�n sebebi her bir dosya topland���nda 10 puan olmas�)
	if (puan == say * 10)
	{
		//e�er cikisa ula�t�ysan while d�ng�s�ndeki stopGame de�i�kenini 0 a ayarla, b�ylece d�ng� dursun ve oyun bitsin, yeni konumda "cikis" in 'c' karakteri var m� diye kontrol et
		if (screen[konumX][(konumY + 1) % 96] == 'c')
		{
			//while d�ng�s�n� durdurmak i�in stopGame de�i�keninin de�erini 0 a ayarla, oyun dursun
			oyunaDevam = 0;
		}
	}

	//oyunda yanmay� ayarla
	//konumY ile 1 i toplayarak sat�r say�s�n�n artmas�n�, b�ylece sa�a hareket etmeyi sa�la, ayn� zamanda sat�r say�s�n�n gerekli olan k�sm�na(oyunun d��� '\n' hari�) mod al ki(%96) konumY 95 say�s�n� a�amas�n. E�er yeni konumda ' ' varsa oraya ilerle ve karakteri oraya koy
	if (screen[konumX][(konumY + 1) % 96] == 'G')
	{
		//mevcut konumu temizle
		oyunaDevam = 0;
		beceremedi = 1;
	}
}

void beklet(int milisaniye)
{
	//int �n depolayabilece�i en k���k de�erin bir fazlas�n� i de�i�kenine at(de�i�kenin depolayabilece�i s�n�rdan m�mk�n oldu�unca uzak durmak i�in).
	int i = -2147483647;
	//d�ng�de i yi kullanmamak(for da oldu�undan i devamli de�i�iyor) i�in ge�ici de�i�ken tan�mla
	int gecici = i;
	//1 milisaniye = 715827 tane d�ng�ye denk geldi�i i�in fonksiyonun parametresi olan milisaniye ile �arp ve gecici de�i�kenin �st�ne ekle. B�ylece d�ng� asl�nda sadece 715827(Asl�nda bu sayi 1 milisaniye)*milisaniye(parametre olarak gelen ka� milisaniye olmas�n� belirledi�imiz de�i�ken) kez d�nm�� olacak.
	for (; i<(milisaniye * 715827 + gecici); i++);
}

void guvenlikHareket()
{
	//yon de�i�keniyle hangi y�nde hareket edilecek, i de�i�keni d�ng� i�in
	int yon, i;
	//4 kez bu i�lemi her bir g�revli i�in yap.
	for (i = 0; i<4; i++)
	{
		//rand() fonksiyonuyla rastgele say� al ve 4 e modunu alarak s�n�r� 4 olarak koy. B�ylece 0,1,2 ve 3 say�lar�na sahip olaca��z.
		yon = rand() % 4;

		//yon de�i�keninin de�erine gore fonksiyon �a��r
		switch (yon)
		{
		case 0:
			//saga hareket ettir, i de�i�keniyle hangi g�revli i�in yapaca��m�z� fonksiyona belirttik
			sagaHareketGuvenlik(i);
			break;
		case 1:
			//sola hareket ettir, i de�i�keniyle hangi g�revli i�in yapaca��m�z� fonksiyona belirttik
			solaHareketGuvenlik(i);
			break;
		case 2:
			///yukar� hareket ettir, i de�i�keniyle hangi g�revli i�in yapaca��m�z� fonksiyona belirttik
			yukariHareketGuvenlik(i);
			break;
		case 3:
			//asagi hareket ettir, i de�i�keniyle hangi g�revli i�in yapaca��m�z� fonksiyona belirttik
			asagiHareketGuvenlik(i);
			break;
		}
	}
}

void sagaHareketGuvenlik(int i)
{
	//E�er haritan�n en sa��nda de�ilse sa�a hareket et.
	if (guvenlik[i][1] != 95)
	{
		//bir sa�daki karakteri kontrol et, e�er oyuncu 'A' orada ise oyunaDevam de�i�kenini 0 a ayarla(oyun bitecek demek), beceremedi de�i�kenini 1 e ayarla(oyunu beceremedi demek)
		if (screen[guvenlik[i][0]][(guvenlik[i][1] + 1) % 96] == 'A')
		{
			oyunaDevam = 0;
			beceremedi = 1;
		}
		
		//d�ng� i�in de�i�ken
		int m=1;
		//E�er sa� karakter '*' bir gizli dosya ise �st�nden atlan�lacak('*' karakterinin sa��na ge�ilecek).
		if(screen[guvenlik[i][0]][(guvenlik[i][1] + m) % 96] == '*')
		{
			//de�i�keni artt�r ki bir di�er karakteri kontrol etsin.
			m++;
			//'*' olmayan bir karakter bulana dek sa�a git.
			while(screen[guvenlik[i][0]][(guvenlik[i][1] + m) % 96] == '*')
			m++;
			
			//mevcut konumu temizle
			screen[guvenlik[i][0]][guvenlik[i][1]] = ' ';

			//yeni konuma karakteri koy
			screen[guvenlik[i][0]][(guvenlik[i][1] + m) % 96] = 'G';

			//guvenlik[i][1] i sonraki kullan�m i�in g�ncelle.
			guvenlik[i][1] = (guvenlik[i][1] + m) % 96;
		}

		//g�venli�in kolonunu bir artt�r ve bo� mu diye kontrol et. Ayr�ca %96 ile harita s�n�rlar� i�erisinde tut
		if (screen[guvenlik[i][0]][(guvenlik[i][1] + 1) % 96] == ' ')
		{
			//mevcut konumu temizle
			screen[guvenlik[i][0]][guvenlik[i][1]] = ' ';

			//yeni konuma karakteri koy
			screen[guvenlik[i][0]][(guvenlik[i][1] + 1) % 96] = 'G';

			//guvenlik[i][1] i sonraki kullan�m i�in g�ncelle.
			guvenlik[i][1] = (guvenlik[i][1] + 1) % 96;
		}
	}
}

void solaHareketGuvenlik(int i)
{

		//E�er haritan�n en solunda de�ilse sola hareket et.
		if (guvenlik[i][1] != 0)
		{
		//bir soldaki karakteri kontrol et, e�er oyuncu 'A' orada ise oyunaDevam de�i�kenini 0 a ayarla(oyun bitecek demek), beceremedi de�i�kenini 1 e ayarla(oyunu beceremedi demek)
		if (screen[guvenlik[i][0]][(guvenlik[i][1] - 1) % 96] == 'A')
		{
			oyunaDevam = 0;
			beceremedi = 1;
		}
		
		//d�ng� i�in de�i�ken
		int m=1;
		//E�er sol karakter '*' bir gizli dosya ise �st�nden atlan�lacak('*' karakterinin soluna ge�ilecek).
		if(screen[guvenlik[i][0]][(guvenlik[i][1] - m) % 96] == '*')
		{
			//de�i�keni artt�r ki bir di�er karakteri kontrol etsin.
			m++;
			//'*' olmayan bir karakter bulana dek sola git.
			while(screen[guvenlik[i][0]][(guvenlik[i][1] - m) % 96] == '*')
			m++;
			
			//mevcut konumu temizle
			screen[guvenlik[i][0]][guvenlik[i][1]] = ' ';

			//yeni konuma karakteri koy
			screen[guvenlik[i][0]][(guvenlik[i][1] - m) % 96] = 'G';

			//guvenlik[i][1] i sonraki kullan�m i�in g�ncelle.
			guvenlik[i][1] = (guvenlik[i][1] - m) % 96;
		}

		//g�venli�in kolonunu bir artt�r ve bo� mu diye kontrol et. Ayr�ca %96 ile harita s�n�rlar� i�erisinde tut
		if (screen[guvenlik[i][0]][(guvenlik[i][1] - 1) % 96] == ' ')
		{
			//mevcut konumu temizle
			screen[guvenlik[i][0]][guvenlik[i][1]] = ' ';

			//yeni konuma karakteri koy
			screen[guvenlik[i][0]][(guvenlik[i][1] - 1) % 96] = 'G';

			//guvenlik[i][1] i sonraki kullan�m i�in g�ncelle.
			guvenlik[i][1] = (guvenlik[i][1] - 1) % 95;
		}
	}
}

void yukariHareketGuvenlik(int i)
{
	//En yukar�da olup olunmad���n� kontrol etmek i�in(sat�r olarak)
	if (guvenlik[i][0] != 0)
	{
		//d�ng� i�in de�i�ken
		int m=1;
		//E�er yukar� karakter '*' bir gizli dosya ise �st�nden atlan�lacak('*' karakterinin yukar�s�na ge�ilecek).
		if(screen[(guvenlik[i][0] - m) % 10][guvenlik[i][1]] == '*')
		{
			//de�i�keni artt�r ki bir di�er karakteri kontrol etsin.
			m++;
			//'*' olmayan bir karakter bulana dek yukar� git.
			while(screen[(guvenlik[i][0] - m) % 10][guvenlik[i][1]] == '*')
			m++;
			
			//mevcut konumu temizle
			screen[guvenlik[i][0]][guvenlik[i][1]] = ' ';

			//yeni konuma karakteri koy
			screen[(guvenlik[i][0] - m) % 10][guvenlik[i][1]] == 'G';

			//guvenlik[i][0] � sonraki kullan�m i�in g�ncelle.
			guvenlik[i][0] = (guvenlik[i][0] - m) % 10;	
		}
			
		//Sat�r� 1 azaltarak yukar� ��k ve oray� bo�mu kontrol et.
		if (screen[(guvenlik[i][0] - 1) % 10][guvenlik[i][1]] == ' ')
		{
			//mevcut konumu temizle
			screen[guvenlik[i][0]][guvenlik[i][1]] = ' ';

			//yeni konuma karakteri koy
			screen[(guvenlik[i][0] - 1) % 10][guvenlik[i][1]] = 'G';

			//guvenlik[i][0] � g�ncelle
			guvenlik[i][0] = (guvenlik[i][0] - 1) % 10;
		}

		//yanmay� ayarla
		if (screen[(guvenlik[i][0] - 1) % 10][guvenlik[i][1]] == 'A')
		{
			oyunaDevam = 0;
			beceremedi = 1;
		}
	}
}

void asagiHareketGuvenlik(int i)
{
	//E�er en a�a��da de�ilse a�a�� hareket et.
			if (guvenlik[i][0] != 9)
			{
		//d�ng� i�in de�i�ken
		int m=1;
		//E�er a�a��daki karakter '*' bir gizli dosya ise �st�nden atlan�lacak('*' karakterinin a�a��s�na ge�ilecek).
		if(screen[(guvenlik[i][0] + m) % 10][guvenlik[i][1]] == '*')
		{
			//de�i�keni artt�r ki bir di�er karakteri kontrol etsin.
			m++;
			//'*' olmayan bir karakter bulana dek a�a�� git.
			while(screen[(guvenlik[i][0] + m) % 10][guvenlik[i][1]] == '*')
			m++;
			
							//mevcut konumu temizle
							screen[guvenlik[i][0]][guvenlik[i][1]] = ' ';

							//yeni konuma karakteri koy
							screen[(guvenlik[i][0] + m) % 10][guvenlik[i][1]] = 'G';

							//guvenlik[i][0] � sonraki kullan�m i�in g�ncelle
							guvenlik[i][0] = (guvenlik[i][0] + m) % 10;
		}

		//Sat�ra bir ekle ki a�a�� gitmi� ol, oray� bo� mu diye kontrol et.
		if (screen[(guvenlik[i][0] + 1) % 10][guvenlik[i][1]] == ' ')
		{
			//mevcut konumu temizle
			screen[guvenlik[i][0]][guvenlik[i][1]] = ' ';

			//yeni konuma karakteri koy
			screen[(guvenlik[i][0] + 1) % 10][guvenlik[i][1]] = 'G';

			//guvenlik[i][0] � g�ncelle
			guvenlik[i][0] = (guvenlik[i][0] + 1) % 10;
		}
		
		//bir a�a��daki karakteri kontrol et, e�er oyuncu 'A' orada ise oyunaDevam de�i�kenini 0 a ayarla(oyun bitecek demek), beceremedi de�i�kenini 1 e ayarla(oyunu beceremedi demek)
		if (screen[(guvenlik[i][0] + 1) % 10][guvenlik[i][1]] == 'A')
		{
			oyunaDevam = 0;
			beceremedi = 1;
		}
	}
}

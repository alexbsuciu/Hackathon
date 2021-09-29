
#pragma warning(disable : 4996)

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <string.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
#include <vector>
using namespace std;
using namespace sf;


sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!", sf::Style::Titlebar | sf::Style::Close);

// variabile globale

int n;

// clasa pentru porci --------------------


class Porcusori {
private:
	int numar;
	string tip;

public:
	Porcusori(int nrMaluma, string tipMaluma)
	{
		tip = tipMaluma;
		numar = nrMaluma;
	}
	Porcusori()
	{
		numar = 0;
		tip = "";
	}
	void setNumber(int nrMaluma)
	{
		numar = nrMaluma;
	}
	void setType(string tipMaluma)
	{
		tip = tipMaluma;
	}
	Porcusori(Porcusori& p)
	{
		p.numar = numar;
		p.tip = tip;
	}

	~Porcusori()
	{
	}

	string getType()
	{
		return tip;
	}

	int getNumber()
	{
		return numar;
	}
};

// clasa pentru rezervari --------------------

class Airbnb {
private:
	Porcusori* porci;
	string data_populare;
	string data_eliberare;

public:
	Airbnb(Porcusori& p, string data_p, string data_e)
	{
		porci = &p;
		data_populare = data_p;
		data_eliberare = data_e;
	}

	Airbnb()
	{
		porci = new Porcusori;
		data_populare = "";
		data_eliberare = "";
	}

	~Airbnb()
	{
		delete porci;
	}

	string getDateP()
	{
		return data_populare;
	}

	string getDateE()
	{
		return data_eliberare;
	}

	string getTip()
	{
		return porci->getType();
	}

	int getNumar()
	{
		return porci->getNumber();
	}

	void setDateP(string dpop)
	{
		data_populare = dpop;
	}

	void setDateE(string delib)
	{
		data_eliberare = delib;
	}

	void setType(string tip)
	{
		porci->setType(tip);
	}

	void setNumar(int nr)
	{
		porci->setNumber(nr);
	}

	Airbnb& operator = (Airbnb& m)
	{
		if (&m != this)
		{
			setType(m.getTip());
			setNumar(m.getNumar());
			setDateE(m.getDateE());
			setDateP(m.getDateP());
		}
		return *this;
	}

};

// clasa pentru hala

class Hala {
private:
	Airbnb* stiva;
	bool ocupat;
	int istoric;
	int contor = 0;
public:
	Hala(int ist, Airbnb* st, bool ocp)
	{
		stiva = st;
		ocupat = ocp;
		istoric = ist;
	}

	Hala()
	{
		stiva = new Airbnb[500];
		ocupat = 0;
		istoric = 0;
	}

	Airbnb* getStiva()
	{
		return stiva;
	}

	bool getOc()
	{
		return ocupat;
	}

	int getIst()
	{
		return istoric;
	}

	void setstiva(Airbnb* s)
	{
		stiva = s;
	}

	void setOc(bool oc)
	{
		ocupat = oc;
	}

	void setIst(int ist)
	{
		istoric = ist;
	}
};

Hala h[500];

void citire()
{
	ifstream f("data.txt");
	f >> n;
	for (int i = 0; i < n; i++)
	{
		bool ocup;
		f >> ocup;
		h[i].setOc(ocup);
		int ist;
		f >> ist;
		h[i].setIst(ist);
		f.get();
		Airbnb* a = h[i].getStiva();
		char temp[50];
		for (int j = 0; j < ist; j++)
		{
			f.getline(temp, 50);
			char* s = strtok(temp, ",");
			string tip(s);
			a[j].setType(s);
			s = strtok(NULL, ",");
			int nr = atoi(s);
			a[j].setNumar(nr);
			s = strtok(NULL, ",");
			string dataP(s);
			a[j].setDateP(dataP);
			s = strtok(NULL, ",");
			string dataE(s);
			a[j].setDateE(dataE);
		}
		h[i].setstiva(a);
	}
	f.close();
}

void adaugareBoxa(int nr1,string type,string spP,string spE)
{
	
	int ind = 0;
	for (int i = 0; i < n; i++)
	{
		ind = i;
		if (h[i].getOc() == 0)
			break;
	}
	int nou = h[ind].getIst();
	nou++;
	h[ind].setIst(nou);
	h[ind].setOc(1);
	Airbnb* s = h[ind].getStiva();
	s[nou - 1].setType(type);
	s[nou - 1].setNumar(nr1);
	s[nou - 1].setDateP(spP);
	s[nou - 1].setDateE(spE);
	h[ind].setstiva(s);
}



void stergere(int index)
{
	h[index].setOc(0);
}

void salvare()
{
	ofstream f("data.txt");
	f << n << "\n";
	for (int i = 0; i < n; i++)
	{
		f << h[i].getOc() << "\n";
		f << h[i].getIst() << "\n";
		int yes = h[i].getIst();
		for (int j = 0; j < yes; j++)
		{
			f << h[i].getStiva()[j].getTip() << ",";
			f << h[i].getStiva()[j].getNumar() << ",";
			f << h[i].getStiva()[j].getDateP() << ",";
			f << h[i].getStiva()[j].getDateE() << "\n";
		}
	}
	f.close();
}







class FileManipulationBoxe {
    fstream openData;
	bool alegere=false;
	string nr_boxe=to_string(n);
public:
	void getDataFromFile()
	{

		openData.open("dataBoxe.txt", fstream::in);
		openData >> alegere;
		
		openData.close();
	}
	void saveToFile()
	{
		openData.open("dataBoxe.txt", fstream::out);
		openData << alegere<<endl;
		openData.close();
	}
	bool getState()
	{
		return alegere;
	}
	string getNrBoxe()
	{
		return nr_boxe;
	}
	void setState(bool state)
	{
		alegere = state;
	}
	void setNrBoxe(string boxe)
	{
		nr_boxe = boxe;
	}
};



class Texturi {
	sf::Texture THala;
	sf::Sprite SHala;
	sf::Texture THala2;
	sf::Sprite SHala2;
	sf::Texture TAntonia;
	sf::Sprite SAntonia;
	sf::Texture TSageataUP;
	sf::Sprite SSageataUP;
	sf::Texture TSageataDown;
	sf::Sprite SSageataDown;
	sf::Texture TButonel;
	sf::Sprite SButonel;
	sf::Texture TX;
	sf::Sprite SX;
	sf::Texture TPatrat;
	sf::Sprite SPatrat;
	sf::Texture TDreptunghi;
	sf::Sprite SDreptunghi;
public:
	Texturi()
	{

		TPatrat.loadFromFile("patrat.png");
		TPatrat.setSmooth(true);
		SPatrat.setTexture(TPatrat);
		SPatrat.setScale(1, 1);
		SPatrat.setPosition(0, 0);


		THala.loadFromFile("Hala.png");
		THala.setSmooth(true);
		SHala.setTexture(THala);
		SHala.setScale(1, 1);
		SHala.setPosition(0, 0);

		TDreptunghi.loadFromFile("dreptunghi.png");
		TDreptunghi.setSmooth(true);
		SDreptunghi.setTexture(TDreptunghi);
		SDreptunghi.setScale(1, 1);
		SDreptunghi.setPosition(1190, 12);


		TX.loadFromFile("xsulet.png");
		TX.setSmooth(true);
		SX.setTexture(TX);
		SX.setScale(1, 1);
		SX.setPosition(0, 0);


		TButonel.loadFromFile("butonel.png");
		TButonel.setSmooth(true);
		SButonel.setTexture(TButonel);
		SButonel.setScale(1, 1);
		SButonel.setPosition(0, 0);

		TAntonia.loadFromFile("Antonia.png");
		TAntonia.setSmooth(true);
		SAntonia.setTexture(TAntonia);
		SAntonia.setScale(0.5f, 0.5f);
		SAntonia.setPosition(0, 0);

		TSageataUP.loadFromFile("arrowUP.png");
		TSageataUP.setSmooth(true);
		SSageataUP.setTexture(TSageataUP);
		SSageataUP.setScale(1, 1);
		SSageataUP.setPosition(790, 20);

		TSageataDown.loadFromFile("arrowDown.png");
		TSageataDown.setSmooth(true);
		SSageataDown.setTexture(TSageataDown);
		SSageataDown.setScale(1, 1);
		SSageataDown.setPosition(790, 810);
	}
	Sprite getSpriteHala()
	{
		return  SHala;
	}
	Sprite getButonel()
	{
		return SButonel;
	}
	Sprite getX()
	{
		return SX;
	}
	Sprite getArrowUp()
	{
		return SSageataUP;
	}
	Sprite getArrowDown()
	{
		return SSageataDown;
	}
	Sprite getPatrat()
	{
		return SPatrat;
	}
	Sprite getSpriteAntonia(int x, int y)
	{
		SAntonia.setPosition(x, y);
		return SAntonia;
	}
	Sprite getDreptunghi()
	{
		return SDreptunghi;
	}

};
void setPositionSprite(int pozX, int pozY,Sprite &sprite)
{
	sprite.setPosition(pozX, pozY);
}
class Scris {
	Text text;
	int pozX, pozY;
	string scris;
	public:
	Scris(sf::Font &fontulet,string s,int size,int x,int y,bool cul, sf::Color culoare)
	{
		text.setFont(fontulet);
		scris = s;
		text.setString(scris);
		pozX = x;
		pozY = y;
		text.setCharacterSize(size);
		text.setPosition(x, y);
		if(cul==true)
		text.setFillColor(culoare);
	}
	void setColor(sf::Color cul)
	{
		text.setColor(cul);
	}
	void afisare()
	{
		window.draw(text);
	}
	int getX()
	{
		return pozX;
	}
	int getY()
	{
		return pozY;
	}
	void afisarePozitii()
	{
		cout << "X: " << pozX<<endl;
		cout << "Y: " << pozY << endl;
	}
	void setFont(sf::Font &fontulet)
	{
		text.setFont(fontulet);
	}
	void setScris(string s)
	{
		scris = s;
		text.setString(scris);
	}
	void setPozitii(int x, int y)
	{
		pozX = x;
		pozY = y;
		text.setPosition(pozX, pozY);
	}
	Text getText()
	{
		return text;
	}


};


Texturi texturi;
FileManipulationBoxe fileManipulation;


int ButoaneMeniuPrincipal(Scris PorcBNB,Scris PorcBRBOrange,Scris AfisareHala,Scris AfisareHalaGreen,Scris AfisareStatistica,Scris AfisareStatisticaGreen,Scris Adaugare,Scris AdaugareGreen, Scris Stergere,Scris StergereGreen,Scris Exit,Scris ExitGreen,Scris Reset,Scris ResetGreen)
{
	sf::Vector2i position = sf::Mouse::getPosition(window);

	//*210 dif cu 45  
	if (position.x >= 660 && position.x <= 905 && position.y >= 75 && position.y <= 145)
	{
		PorcBRBOrange.afisare();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1;
		}
	}
	else { PorcBNB.afisare(); }

	if (position.x >= 630 && position.x <= 965 && position.y >= 160 && position.y <= 210)
	{
		AfisareHalaGreen.afisare();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 2;
		}
	}
	else { AfisareHala.afisare(); }

	if (position.x >= 660 && position.x <= 885 && position.y >= 260 && position.y <= 320)
	{
		AfisareStatisticaGreen.afisare();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 3;
		}
	}
	else { AfisareStatistica.afisare(); }

	if (position.x >= 600 && position.x <= 960 && position.y >= 360 && position.y <= 420)
	{
		AdaugareGreen.afisare();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 4;
		}
	}
	else { Adaugare.afisare(); }

	if (position.x >= 620 && position.x <= 950 && position.y >= 460 && position.y <= 520)
	{
		StergereGreen.afisare();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 5;
		}
	}
	else { Stergere.afisare(); }

	if (position.x >= 710 && position.x <= 840 && position.y >= 560 && position.y <= 625)
	{
		ExitGreen.afisare();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 6;
		}
	}
	else { Exit.afisare(); }
	 /*
	if (position.x >= 1450 && position.x <= 1580 && position.y >= 830 && position.y <= 900)
	{
		ResetGreen.afisare();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 7;
		}
	}
	else { Reset.afisare(); }
	*/
	return 1;
}



void mutareCursor(int x, int y)
{

		sf::Vector2i poz(x, y);
		sf::Mouse::setPosition(poz, window);

}

void REEEEEantonix(Scris &ceva,int index, int contoras)
{
	ceva.setScris(to_string(h[index].getStiva()[contoras].getNumar()));
	ceva.setPozitii(1190, 16);
	ceva.afisare();
	ceva.setScris(h[index].getStiva()[contoras].getTip());
	ceva.setPozitii(1190, 86);
	ceva.afisare();
	ceva.setScris(h[index].getStiva()[contoras].getDateP());
	ceva.setPozitii(1190, 156);
	ceva.afisare();
	ceva.setScris(h[index].getStiva()[contoras].getDateE());
	ceva.setPozitii(1190, 226);
	ceva.afisare();

}

int main()
{
	citire();
	fileManipulation.setNrBoxe(to_string(n));
	window.setFramerateLimit(60);
	sf::Font font;

	font.loadFromFile("Amaranth-Regular.otf");
    Scris PorcBNB(font, "PorcBNB", 75, 640, 60, false,sf::Color(255, 255, 255));
	Scris PorcBNBOrange(font, "PorcBNB", 75, 640, 60, true, sf::Color(255, 153, 0));
	Scris AfisareHala(font, "Vizualizare hala", 55, 590, 160, false, sf::Color(255, 255, 255));
	Scris AfisareHalaGreen(font, "Vizualizare hala", 55, 590, 160, true, sf::Color(0, 204, 0));
	Scris AfisareStatistica(font, "Statistica", 55, 660, 260, false, sf::Color(255, 255, 255));
	Scris AfisareStatiscaGreen(font, "Statistica", 55, 660, 260, true, sf::Color(0, 204, 0));
	Scris Adaugare(font, "Adaugare boxa", 55, 600, 360, false, sf::Color(255, 255, 255));
	Scris AdaugareGreen(font, "Adaugare boxa", 55, 600, 360, true, sf::Color(0, 204, 0));
	Scris Stergere(font, "Stergere boxa", 55, 620, 460, false, sf::Color(255, 255, 255));
	Scris StergereGreen(font, "Stergere boxa", 55, 620, 460, true, sf::Color(0, 204, 0));
	Scris Exit(font, "Iesire", 55, 710, 560, false, sf::Color(255, 255, 255));
	Scris ExitGreen(font, "Iesire", 55, 710, 560, true, sf::Color(0, 204, 0));
	Scris Reset(font, "Reset", 55, 1450, 830, false, sf::Color(255, 255, 255));
	Scris ResetGreen(font, "Reset", 55, 1450, 830, true, sf::Color(0, 204, 0));
	Scris NrPorciScris(font, "_", 55, 855, 400, false, sf::Color(255, 255, 255));
	Scris IntroduPorcii(font, "Cate boxe? :", 55, 550, 400, false, sf::Color(255, 255, 255));
	Scris IntroduNrPorci(font, "Numarul de porci? :", 55, 450, 400, false, sf::Color(255, 255, 255));
	Scris IntroduTipulDePorci(font, "Tipul de porci? :", 55, 550, 400, false, sf::Color(255, 255, 255));
	Scris IntroduDataPopularii(font, "Data popularii? :", 55, 550, 400, false, sf::Color(255, 255, 255));
	Scris IntroduDataEliberarii(font, "Data eliberarii? :", 55, 550, 400, false, sf::Color(255, 255, 255));
	Scris IntroduIndexStergere(font, "Numarul boxei de doriti sa o stergeti? :", 55, 250, 400, false, sf::Color(255, 255, 255));
	Scris Numerotare(font,"", 75, 0, 0, false, sf::Color(255, 255, 255));
	Scris Informatii(font, "", 75, 640, 60, false, sf::Color(255, 255, 255));
	Scris Statistica(font, "", 75, 540, 60, false, sf::Color(255, 255, 255));
	int menu = 0,i=0,j=0,nr = 0,contor=0,ok=0,index=0,contoras=0,scroafe = 0, pmari = 0, pmici = 0;
	string varNR,varTIP,varDATAP,varDATAE,varSter;

     fileManipulation.getDataFromFile();
	string nr_porci=fileManipulation.getNrBoxe();
	bool nr_porci_bool = fileManipulation.getState();

	if (nr_porci_bool == true)
	{
		menu = 1;
		NrPorciScris.setScris(fileManipulation.getNrBoxe());

	}

	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			/*
			if (event.type == sf::Event::TextEntered && nr_porci_bool==false)
			{
				if (event.text.unicode < 128)
				{
					if (static_cast<char>(event.text.unicode) >= string("0") && static_cast<char>(event.text.unicode) <= string("9"))
					{


						nr_porci += event.text.unicode;
						NrPorciScris.setScris(nr_porci);
						IntroduPorcii.afisare();
						NrPorciScris.afisare();

					}
					if (static_cast<char>(event.text.unicode) == 13)
					{  
						cout << nr_porci<<endl;
						n = stoi(nr_porci);
						ofstream ceva("data.txt");
						ceva << n<<endl;
						for (i = 0; i < n; i++)
						{
							ceva << 0 << endl;
							ceva << 0 << endl;
						}
						ceva.close();
						nr_porci_bool = true;
						menu = 1;
						citire();
						
						fileManipulation.setState(true);
						fileManipulation.setNrBoxe(nr_porci);
						fileManipulation.saveToFile();
						
					}
					if (static_cast<char>(event.text.unicode) == 8)
					{
						nr_porci.erase(nr_porci.size()-1, 1);
						NrPorciScris.setScris(nr_porci);
					}
				}
			}
             */
			if (event.type == sf::Event::MouseWheelMoved && ok==1)
			{
			     	contoras++;
					if (contoras >= h[index].getIst())
						contoras = 0;
					Informatii.setScris(to_string(h[index].getStiva()[contoras].getNumar()));
					Informatii.setPozitii(1190, 16);
					Informatii.afisare();
					Informatii.setScris(h[index].getStiva()[contoras].getTip());
					Informatii.setPozitii(1190, 46);
					Informatii.afisare();
					Informatii.setScris(h[index].getStiva()[contoras].getDateP());
					Informatii.setPozitii(1190, 66);
					Informatii.afisare();
					Informatii.setScris(h[index].getStiva()[contoras].getDateE());
					Informatii.setPozitii(1190, 6);
					Informatii.afisare();

				}



			if (event.type == sf::Event::TextEntered && menu==5)
			{
				if (event.text.unicode < 128)
				{
					if (static_cast<char>(event.text.unicode) >= string("0") && static_cast<char>(event.text.unicode) <= string("9"))
					{


						varSter += event.text.unicode;
						NrPorciScris.setScris(varSter);
						NrPorciScris.setPozitii(1200, 400);

					}
					if (static_cast<char>(event.text.unicode) == 13)
					{
						stergere(stoi(varSter));
						salvare();

						varSter = "";
						menu = 1;

					}
					if (static_cast<char>(event.text.unicode) == 8)
					{
						varSter.erase(varSter.size() - 1, 1);
						NrPorciScris.setScris(varSter);
					}
				}
			}


			if (event.type == sf::Event::TextEntered && menu==4)
			{
				if (event.text.unicode < 128)
				{
					if(nr==0)
					if (static_cast<char>(event.text.unicode) >= string("0") && static_cast<char>(event.text.unicode) <= string("9"))
					{
						
						varNR += event.text.unicode;
						NrPorciScris.setScris(varNR);
						NrPorciScris.setPozitii(940, 400);
					}

					if(nr==1)
				   if (static_cast<char>(event.text.unicode) >= string("0") && static_cast<char>(event.text.unicode) <= string("z"))
					{
							varTIP += event.text.unicode;
							NrPorciScris.setScris(varTIP);
							NrPorciScris.setPozitii(950, 400);

					}
					if (nr == 2)
						if (static_cast<char>(event.text.unicode) >= string("0") && static_cast<char>(event.text.unicode) <= string("z"))
						{
							varDATAP += event.text.unicode;
							NrPorciScris.setScris(varDATAP);
							NrPorciScris.setPozitii(970, 400);

						}
					if (nr == 3)
						if (static_cast<char>(event.text.unicode) >= string("0") && static_cast<char>(event.text.unicode) <= string("z"))
						{
							varDATAE += event.text.unicode;
							NrPorciScris.setScris(varDATAE);
							NrPorciScris.setPozitii(970, 400);

						}
					if (static_cast<char>(event.text.unicode) == 13)
					{
						nr++;
						if (nr == 4)
						{
							menu = 1;
							nr = 0;
							adaugareBoxa(stoi(varNR), varTIP, varDATAP, varDATAE);
							salvare();
							varNR = "";
							varTIP = "";
							varDATAP = "";
							varDATAE = "";
						}
						

					}
					if (static_cast<char>(event.text.unicode) == 8)
					{
						if (nr == 0)
						{
							varNR.erase(varNR.size() - 1, 1);
							NrPorciScris.setScris(varNR);
						}
						if (nr == 1)
						{
							varTIP.erase(varTIP.size() - 1, 1);
							NrPorciScris.setScris(varTIP);
						}
						if (nr == 2)
						{
							varDATAP.erase(varDATAP.size() - 1, 1);
							NrPorciScris.setScris(varDATAP);
						}
						if (nr == 3)
						{
							varDATAE.erase(varDATAE.size() - 1, 1);
							NrPorciScris.setScris(varDATAE);
						}
					}
				}
			}





		}
		ok = 0;
		if (menu == 0)
		{
			IntroduPorcii.afisare();
			NrPorciScris.afisare();
		}
		if (menu == 1)
		{
             menu = ButoaneMeniuPrincipal(PorcBNB,PorcBNBOrange,AfisareHala,AfisareHalaGreen,AfisareStatistica,AfisareStatiscaGreen, Adaugare,AdaugareGreen,Stergere, StergereGreen, Exit,ExitGreen,Reset,ResetGreen);
		}
		if (menu == 2)
		{
			citire();
			window.draw(texturi.getSpriteHala());
			Sprite buton = texturi.getButonel();
			Sprite Xul = texturi.getX();
			sf::Vector2i position = sf::Mouse::getPosition(window);

			if (2 * 0 + 0 + 6 * contor > stoi(fileManipulation.getNrBoxe()))
				Numerotare.setColor(sf::Color::Red);

			Numerotare.setScris(to_string(2 * 0 + 0 + 6 * contor));
			Numerotare.setPozitii(250, 33);
			Numerotare.afisare();
			Numerotare.setColor(sf::Color::White);
			if (2 * 0 + 1 + 6 * contor > stoi(fileManipulation.getNrBoxe()))
				Numerotare.setColor(sf::Color::Red);
			Numerotare.setScris(to_string(2 * 0 + 1 + 6 * contor));
			Numerotare.setPozitii(250, 33 * 1 * 10);
			Numerotare.afisare();
			Numerotare.setColor(sf::Color::White);
			if (2 * 1 + 0 + 6 * contor > stoi(fileManipulation.getNrBoxe()))
				Numerotare.setColor(sf::Color::Red);
			Numerotare.setScris(to_string(2 * 1 + 0 + 6 * contor));
			Numerotare.setPozitii(250, 33 * 2 * 10);
			Numerotare.afisare();
			Numerotare.setColor(sf::Color::White);
			if (2 * 1 + 1 + 6 * contor > stoi(fileManipulation.getNrBoxe()))
				Numerotare.setColor(sf::Color::Red);
			Numerotare.setScris(to_string(2 * 1 + 1 + 6 * contor));
			Numerotare.setPozitii(930, 33);
			Numerotare.afisare();
			Numerotare.setColor(sf::Color::White);
			if (2 * 2 + 0 + 6 * contor > stoi(fileManipulation.getNrBoxe()))
				Numerotare.setColor(sf::Color::Red);
			Numerotare.setScris(to_string(2 * 2+ 0 + 6 * contor));
			Numerotare.setPozitii(930, 33 * 1 * 10);
			Numerotare.afisare();
			Numerotare.setColor(sf::Color::White);
			if (2 * 2 + 1 + 6 * contor > stoi(fileManipulation.getNrBoxe()))
				Numerotare.setColor(sf::Color::Red);
			Numerotare.setScris(to_string(2 * 2 + 1 + 6 * contor));
			Numerotare.setPozitii(930, 33 * 2 * 10);
			Numerotare.afisare();
			Numerotare.setColor(sf::Color::White);

			for (i = 0; i < 3; i++)
			{
				if (h[i + 6 * contor].getOc() == true)
				{
			
					if(i==0)
					setPositionSprite(600, 33, Xul);
					else{setPositionSprite(600, 33 * i * 10, Xul); }
				}
				window.draw(Xul);
			}
			for (i = 0; i < 3; i++)
			{
				if (h[i+3 + 6 * contor].getOc() == true)
				{
					if (i == 0)
						setPositionSprite(1280, 33, Xul);
					else { setPositionSprite(1280, 33 * i * 10, Xul); }
				}
				window.draw(Xul);
			}
					
			if (position.x >= 600 && position.x <= 660 && position.y >= 210 && position.y <= 270)
			{
				window.draw(texturi.getDreptunghi());
				ok = 1;
				index = 2 * 0 + 0 + 6 * contor;
				REEEEEantonix(Informatii, index, contoras);
			}
			if (position.x >= 600 && position.x <= 660 && position.y >= 500 && position.y <= 560)
			{
				window.draw(texturi.getDreptunghi());
				ok = 1;
				index = 2 * 0 + 1 + 6 * contor;
				REEEEEantonix(Informatii, index, contoras);
			}
			if (position.x >= 600 && position.x <= 660 && position.y >= 800 && position.y <= 860)
			{
				window.draw(texturi.getDreptunghi());
				ok = 1;
				index = 2 * 1 + 0 + 6 * contor;
				REEEEEantonix(Informatii, index, contoras);
			}
			if (position.x >= 937 && position.x <= 997 && position.y >= 210 && position.y <= 270)
			{
				window.draw(texturi.getDreptunghi());
				ok = 1;
				index = 2 * 1 + 1 + 6 * contor;
				REEEEEantonix(Informatii, index, contoras);
			}
			if (position.x >= 937 && position.x <= 997 && position.y >= 500 && position.y <= 560)
			{
				window.draw(texturi.getDreptunghi());
				ok = 1;
				index = 2 * 2 + 0 + 6 * contor;
				REEEEEantonix(Informatii, index, contoras);
			}
			if (position.x >= 937 && position.x <= 997 && position.y >= 800 && position.y <= 860)
			{
				window.draw(texturi.getDreptunghi());
				ok = 1;
				index = 2 * 2 + 1 + 6 * contor;
				REEEEEantonix(Informatii, index, contoras);

			}
			setPositionSprite(600, 210, buton);
			window.draw(buton);
			setPositionSprite(600, 500, buton);
			window.draw(buton);
			setPositionSprite(600, 800, buton);
			window.draw(buton);
			setPositionSprite(937, 210, buton);
			window.draw(buton);
			setPositionSprite(937, 500, buton);
			window.draw(buton);
			setPositionSprite(937, 800, buton);

			window.draw(buton);
			if (position.x >= 780 && position.x <= 820 && position.y >= 12 && position.y <= 85)
			{
				Sprite s = texturi.getArrowUp();
				s.setColor(sf::Color::Green);
				window.draw(s);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					
					if ( stoi(fileManipulation.getNrBoxe())- (contor) * 6 >= 6)
					{
						mutareCursor(800, 450);
						contor++;
					}

				}
			}
			else { window.draw(texturi.getArrowUp()); }



			if (position.x >= 780 && position.x <= 820 && position.y >= 800 && position.y <= 875)
			{

				Sprite s1 = texturi.getArrowDown();
				s1.setColor(sf::Color::Green);
				window.draw(s1);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (contor - 1 >= 0)
					{
						mutareCursor(800, 450);
						contor--;
					}
				}
			}
			else { window.draw(texturi.getArrowDown()); }

			window.draw(texturi.getPatrat());

			//*cout << position.x << " " << position.y << endl;

		}
		if (menu == 3)
		{

			for (i = 0; i < n; i++)
			{
				if (h[i].getOc())
				{
					if (h[i].getStiva()[h[i].getIst() - 1].getTip() == "scroafe")
					{
						scroafe += h[i].getStiva()[h[i].getIst() - 1].getNumar();
					}
					if (h[i].getStiva()[h[i].getIst() - 1].getTip() == "porci mici")
					{
						pmici += h[i].getStiva()[h[i].getIst() - 1].getNumar();
					}
					if (h[i].getStiva()[h[i].getIst() - 1].getTip() == "porci mari")
					{
						pmari += h[i].getStiva()[h[i].getIst() - 1].getNumar();
					}
				}
			}
			Statistica.setScris("Numar scroafe: " + to_string(scroafe));
			Statistica.setPozitii(450, 60);
			Statistica.afisare();
			Statistica.setScris("Numar porci mici: " + to_string(pmici));
			Statistica.setPozitii(450, 150);
			Statistica.afisare();
			Statistica.setScris("Numar porci mari: " + to_string(pmari));
			Statistica.setPozitii(450, 230);
			Statistica.afisare();
			scroafe = 0;
			pmici = 0;
			pmari = 0;

		}
		if (menu == 4)
		{
		

			if (nr == 0)
			{
				NrPorciScris.setScris(varNR);
				IntroduNrPorci.afisare();
				NrPorciScris.afisare();
			}
			if (nr == 1)
			{
				NrPorciScris.setScris(varTIP);
				IntroduTipulDePorci.afisare();
				NrPorciScris.afisare();
			}
			if (nr == 2)
			{
				NrPorciScris.setScris(varDATAP);
				IntroduDataPopularii.afisare();
				NrPorciScris.afisare();
			}
			if (nr == 3)
			{
				NrPorciScris.setScris(varDATAE);
				IntroduDataEliberarii.afisare();
				NrPorciScris.afisare();
			}
		}
		if (menu == 5)
		{
			NrPorciScris.setScris(varSter);
			IntroduIndexStergere.afisare();
			NrPorciScris.afisare();
		}
		if (menu == 6)
		{
			 window.close();
		}
		/*
		if (menu == 7)
		{
			menu = 0;
			nr_porci_bool = false;
			fileManipulation.setState(false);
			fileManipulation.setNrBoxe("");
			nr_porci = "";
			NrPorciScris.setScris(nr_porci);
		}
		*/

		//* daca se apasa esc,se intoarce la meniul principal
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			menu = 1; 
		}

		window.display();
	}
	
	return 0;

}


// sistem control Webasto
// program scris de Nicu FLORICA (niq_ro)
// program testat de George MORSOACA (Tommy)
// versiune 0, simulare program simplu - 16.10.2017, Craiova

#define pompita 10
#define ventilator 11
#define bujie 9
int aerisire = 10000;  // timp pentru ventilare camera (ms)
int tpbujie = 10; // timp mentinere pornita bujie (s)
int tppompa1 = 500;  // timp alimentare pompa la aprindere
int tppompa2 = 1000; // timp alimentare pompa la functionare normala
int pas = 10; // fragmentare crestere turatie ventilator
int turatie = 0;

void setup() {
Serial.begin(9600);
Serial.println("Simulare control Webasto ...");
  
pinMode(pompita, OUTPUT);
pinMode(ventilator, OUTPUT);
pinMode(bujie, OUTPUT);

digitalWrite(pompita, 0);  // pompita oprita
analogWrite(ventilator, 0); // ventilator oprit
digitalWrite(bujie, 0); // bujie stinsa

// se simuleaza asteptarea
Serial.println("Sistem in asteptare !");
Serial.println("---------------------------------");
delay(3000);

// simulam apasare buton de pornire sau comanda de pornire
Serial.println("Se da comanda de pornire !");
// 1) aerisire camera de gaze
analogWrite(ventilator, 255); // ventilator pornit la turatie maxima
Serial.println("Porneste ventilator pentru aerisire camera !");
delay(aerisire);   
analogWrite(ventilator, 0); // ventilator oprit
Serial.println("Se opreste ventilatorul !");
delay(1000); // mica pauza

Serial.println("---------------------------------");
Serial.println("Se initializeaza procedura de aprindere !");
// 2) alimentare bujie, pompa alimentata cu 2 impulsuri pe minut, turatie ventilator in crestere
digitalWrite(bujie, 1);  // alimentare bujie
Serial.println("Bujie aprinsa !");
delay(200); // mica intarziere

for (int i = 0; i<tpbujie; i++)
{
 digitalWrite(pompita, 1); // alimentare pompita
 Serial.println("Pompita alimentata !");  
for (int j = 0; j<pas/2; j++)
{ 
  turatie = 25.5*(10*i+j)/tpbujie;
  analogWrite(ventilator, turatie);  // crestere turatie pompita
  Serial.print("Turatie ventilator: ");
  Serial.print(turatie);
  Serial.println("/255");
  delay(tppompa1/pas);
}
  digitalWrite(pompita, 0); // oprire pompita
  Serial.println("Pompita oprita !");
for (int j = pas/2; j<pas; j++)
{ 
  turatie = 25.5*(10*i+j)/tpbujie;
  analogWrite(ventilator, turatie);  // crestere turatie pompita
  Serial.print("Turatie ventilator: ");
  Serial.print(turatie);
  Serial.println("/255");
  delay(tppompa1/pas);
}
}
digitalWrite(bujie, 0);  // decuplare bujie
Serial.println("Bujie stinsa !");
Serial.println("Terminare secventa de aprindere !");
Serial.println("---------------------------------");
analogWrite(ventilator, 255);  // ventilator la turatie maxima
  Serial.print("Turatie ventilator: ");
  Serial.print("255");
  Serial.println("/255");
}

void loop() {
// 3) functionare normala: ventilator la turatie maxima si pompita alimentata la 1 secunda
  digitalWrite(pompita, 1); // alimentare pompita
  Serial.println("Pompita alimentata !");
  delay(tppompa2);
  digitalWrite(pompita, 0); // oprire pompita
  Serial.println("Pompita oprita !");
  delay(tppompa2);
}

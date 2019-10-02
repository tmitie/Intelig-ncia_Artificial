/*
Para definir o parametros da fuzzy dividi por 3 tendo assim os maximos de cada 
e para ter uma comparação fizemos funções triangular onde seu pico seria a mesma velocidade que na RNA,utilizamos o map para encontrar os valores



*/

#define MAX_VEL 255
#define MIN_VEL 10
#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>

const int motor_1_a =10;
const int motor_1_b =5;
const int motor_2_a =11;
const int motor_2_b =9;
const int motor_1_enable =7;
const int motor_2_enable =8;
const int triggerE =12;
const int echoE =13;
const int triggerD =4;
const int echoD =2;
Fuzzy* fuzzy = new Fuzzy();
void setup() {

pinMode(motor_1_a,OUTPUT);
pinMode(motor_1_b,OUTPUT);
pinMode(motor_2_b,OUTPUT);
pinMode(motor_2_a,OUTPUT);
pinMode(motor_1_enable,OUTPUT);
pinMode(motor_2_enable,OUTPUT);
Serial.begin(9600);


pinMode(triggerE, OUTPUT);
pinMode(echoE,INPUT);
pinMode(triggerD, OUTPUT);
pinMode(echoD,INPUT);

//ligar motores

digitalWrite(motor_1_enable,HIGH);
digitalWrite(motor_2_enable,HIGH);

// Criando o FuzzyInput Distancia Esquerda
  FuzzyInput* distanciaE = new FuzzyInput(1);
  // Criando os FuzzySet que compoem o FuzzyInput distancia
  FuzzySet* smallE = new FuzzySet(0, 100, 100, 224); // Distancia pequena direcionada a ré
  distanciaE->addFuzzySet(smallE); // Adicionando o FuzzySet small em distance
  FuzzySet* halfSmallE = new FuzzySet(150, 320, 320, 373);//Inicio das distancias com sentido positivo
  distanciaE->addFuzzySet(halfSmallE);
  FuzzySet* safeE = new FuzzySet(380, 560, 560, 672); // Distancia segura
  distanciaE->addFuzzySet(safeE); // Adicionando o FuzzySet safe em distance
  FuzzySet* halfBigE = new FuzzySet(600, 730, 730, 896);//
  distanciaE->addFuzzySet(halfBigE);
  FuzzySet* bigE = new FuzzySet(800, 950, 950, 1120); // Distancia grande
  distanciaE->addFuzzySet(bigE); // Adicionando o FuzzySet big em distance

  fuzzy->addFuzzyInput(distanciaE);
  
  // Criando o FuzzyInput Distância Direira
  FuzzyInput* distanciaD = new FuzzyInput(2);
  // Criando os FuzzySet que compoem o FuzzyInput distancia
  FuzzySet* smallD = new FuzzySet(0, 100, 100, 224); // Distancia pequena
  distanciaD->addFuzzySet(smallD); // Adicionando o FuzzySet small em distance
  FuzzySet* halfSmallD = new FuzzySet(150, 320, 320, 373);
  distanciaE->addFuzzySet(halfSmallD);
  FuzzySet* safeD = new FuzzySet(380, 560, 560, 672); // Distancia segura
  distanciaD->addFuzzySet(safeD); // Adicionando o FuzzySet safe em distance
  FuzzySet* halfBigD = new FuzzySet(600, 730, 730, 896);
  distanciaE->addFuzzySet(halfBigD);
  FuzzySet* bigD = new FuzzySet(800, 950, 950, 1120); // Distancia grande
  distanciaD->addFuzzySet(bigD); // Adicionando o FuzzySet big em distance

  fuzzy->addFuzzyInput(distanciaD); // Adicionando o FuzzyInput no objeto Fuzzy

  // Criando o FuzzyOutput velocidade do motor DIREITO
  FuzzyOutput* velocityD = new FuzzyOutput(1);
  // Criando os FuzzySet que compoem o FuzzyOutput velocidade
  FuzzySet* reD = new FuzzySet(-20,  -10,  -10, 0); // ré
  velocityD->addFuzzySet(reD); // Adicionando o FuzzySet ré em velocity
  FuzzySet* slowD = new FuzzySet(0,  45,  45, 85); // Velocidade lenta
  velocityD->addFuzzySet(slowD); // Adicionando o FuzzySet slow em velocity
  FuzzySet* averageD = new FuzzySet(65, 113, 113, 160); // Velocidade normal
  velocityD->addFuzzySet(averageD); // Adicionando o FuzzySet average em velocity
  FuzzySet* fastD = new FuzzySet(140, 194, 194, 255); // Velocidade alta
  velocityD->addFuzzySet(fastD); // Adicionando o FuzzySet fast em velocity

  fuzzy->addFuzzyOutput(velocityD); // Adicionando o FuzzyOutput no objeto Fuzzy

  // Criando o FuzzyOutput velocidade do motor ESQUERDO
  FuzzyOutput* velocityE = new FuzzyOutput(2);
  // Criando os FuzzySet que compoem o FuzzyOutput velocidade
  FuzzySet* reE = new FuzzySet(-20,  -10,  -10, 0); // ré
  velocityE->addFuzzySet(reE); // Adicionando o FuzzySet ré em velocity
  FuzzySet* slowE = new FuzzySet(0,  45,  45, 85); // Velocidade lenta
  velocityE->addFuzzySet(slowE); // Adicionando o FuzzySet slow em velocity
  FuzzySet* averageE = new FuzzySet(65, 113, 113, 160); // Velocidade normal
  velocityE->addFuzzySet(averageE); // Adicionando o FuzzySet average em velocity
  FuzzySet* fastE = new FuzzySet(140, 194, 194, 255); // Velocidade alta
  velocityE->addFuzzySet(fastE); // Adicionando o FuzzySet fast em velocity

  fuzzy->addFuzzyOutput(velocityE); // Adicionando o FuzzyOutput no objeto Fuzzy

  //-------------------- Montando as regras Fuzzy ---------------------------
  
  
  // ******* REGRA 1 para OUTPUT = reD AND reE ********
  FuzzyRuleAntecedent* SmD_SmE = new FuzzyRuleAntecedent(); //1 a
  SmD_SmE -> joinWithAND(smallD,smallE);
  
  FuzzyRuleAntecedent* SmD_SfE = new FuzzyRuleAntecedent(); //1 a
  SmD_SfE -> joinWithAND(smallD,safeE);
  
  FuzzyRuleAntecedent* SmD_BE = new FuzzyRuleAntecedent(); //2 a
  SmD_BE -> joinWithAND(smallD,bigE);
  
  FuzzyRuleAntecedent* SfD_SmE = new FuzzyRuleAntecedent(); //2 a
  SfD_SmE -> joinWithAND(safeD,smallE);
  
  FuzzyRuleAntecedent* BD_SmE = new FuzzyRuleAntecedent(); //3 a
  BD_SmE -> joinWithAND(bigD,smallE);
  
  FuzzyRuleAntecedent* SmD_hSmE = new FuzzyRuleAntecedent(); //3 a
  SmD_hSmE -> joinWithAND(smallD,halfSmallE);
  
  FuzzyRuleAntecedent* hSmD_SmE = new FuzzyRuleAntecedent(); //4 a
  hSmD_SmE -> joinWithAND(halfSmallD,smallE);  
  
  FuzzyRuleAntecedent* hBD_SmE = new FuzzyRuleAntecedent(); //4 a
  hBD_SmE -> joinWithAND(halfBigD,smallE);
  
  FuzzyRuleAntecedent* SmD_hBE = new FuzzyRuleAntecedent(); //5 a   --------------
  SmD_hBE -> joinWithAND(smallD,halfBigE);

  // Este objeto FuzzyRuleAntecedente é que será usada para compor o objeto FuzzyRule 
  FuzzyRuleAntecedent* if_SmD_SmE_OR_SmD_SfE = new FuzzyRuleAntecedent(); //1b
  if_SmD_SmE_OR_SmD_SfE->joinWithOR(SmD_SmE, SmD_SfE); 
  
  FuzzyRuleAntecedent* if_SmD_BE_OR_SfD_SmE = new FuzzyRuleAntecedent(); //1b
  if_SmD_BE_OR_SfD_SmE->joinWithOR(SmD_BE, SfD_SmE); 

  FuzzyRuleAntecedent* if_BD_SmE_OR_SmD_hSmE = new FuzzyRuleAntecedent(); //2b
  if_BD_SmE_OR_SmD_hSmE->joinWithOR(BD_SmE, SmD_hSmE);
  
  FuzzyRuleAntecedent* if_hSmD_SmE_OR_hBD_SmE = new FuzzyRuleAntecedent(); //2b
  if_hSmD_SmE_OR_hBD_SmE->joinWithOR(hSmD_SmE, hBD_SmE); 
  
  FuzzyRuleAntecedent* if_SmD_SmE_OR_SmD_SfE_if_SmD_BE_OR_SfD_SmE = new FuzzyRuleAntecedent(); //1c
  if_SmD_SmE_OR_SmD_SfE_if_SmD_BE_OR_SfD_SmE->joinWithOR(if_SmD_SmE_OR_SmD_SfE, if_SmD_BE_OR_SfD_SmE);  
  
  FuzzyRuleAntecedent* if_BD_SmE_OR_SmD_hSmE_if_if_hSmD_SmE_OR_hBD_SmE = new FuzzyRuleAntecedent(); //1c
  if_BD_SmE_OR_SmD_hSmE_if_if_hSmD_SmE_OR_hBD_SmE->joinWithOR(if_BD_SmE_OR_SmD_hSmE, if_hSmD_SmE_OR_hBD_SmE);
  
  FuzzyRuleAntecedent* if_SmD_SmE_OR_SmD_SfE_if_SmD_BE_OR_SfD_SmE__if_BD_SmE_OR_SmD_hSmE_if_if_hSmD_SmE_OR_hBD_SmE = new FuzzyRuleAntecedent(); //1d
  if_SmD_SmE_OR_SmD_SfE_if_SmD_BE_OR_SfD_SmE__if_BD_SmE_OR_SmD_hSmE_if_if_hSmD_SmE_OR_hBD_SmE->joinWithOR(if_SmD_SmE_OR_SmD_SfE_if_SmD_BE_OR_SfD_SmE, if_BD_SmE_OR_SmD_hSmE_if_if_hSmD_SmE_OR_hBD_SmE); 
  
  FuzzyRuleAntecedent* if_SmD_SmE_OR_SmD_SfE_if_SmD_BE_OR_SfD_SmE__if_BD_SmE_OR_SmD_hSmE_if_if_hSmD_SmE_OR_hBD_SmE__SmD_hBE = new FuzzyRuleAntecedent(); //1d + 5a
  if_SmD_SmE_OR_SmD_SfE_if_SmD_BE_OR_SfD_SmE__if_BD_SmE_OR_SmD_hSmE_if_if_hSmD_SmE_OR_hBD_SmE__SmD_hBE->joinWithOR(if_SmD_SmE_OR_SmD_SfE_if_SmD_BE_OR_SfD_SmE__if_BD_SmE_OR_SmD_hSmE_if_if_hSmD_SmE_OR_hBD_SmE, SmD_hBE);  
  
  FuzzyRuleConsequent* then_VRD_AND_VRE = new FuzzyRuleConsequent();
  then_VRD_AND_VRE->addOutput(reD);
  then_VRD_AND_VRE->addOutput(reE);
 
  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, if_SmD_SmE_OR_SmD_SfE_if_SmD_BE_OR_SfD_SmE__if_BD_SmE_OR_SmD_hSmE_if_if_hSmD_SmE_OR_hBD_SmE__SmD_hBE, then_VRD_AND_VRE);
  fuzzy->addFuzzyRule(fuzzyRule1);


  //********* REGRA 2 para OUTPUT = averangeD AND slowE
  FuzzyRuleAntecedent* hSmD_hSmE = new FuzzyRuleAntecedent(); //1 a
  hSmD_hSmE -> joinWithAND(halfSmallD,halfSmallE);
  
  FuzzyRuleAntecedent* hSmD_SfE = new FuzzyRuleAntecedent(); //1 a
  hSmD_SfE -> joinWithAND(halfSmallD,safeE);

  FuzzyRuleAntecedent* hSmD_hBE = new FuzzyRuleAntecedent(); //2 a
  hSmD_hBE -> joinWithAND(halfSmallD,halfBigE);

  FuzzyRuleAntecedent* if_hSmD_hSmE_OR_hSmD_SfE = new FuzzyRuleAntecedent();//1b
  if_hSmD_hSmE_OR_hSmD_SfE ->joinWithOR(hSmD_hSmE, hSmD_SfE); 

  FuzzyRuleAntecedent* if_hSmD_hSmE_OR_hSmD_SfE__OR__hSmD_hBE = new FuzzyRuleAntecedent();//1b
  if_hSmD_hSmE_OR_hSmD_SfE__OR__hSmD_hBE ->joinWithOR(if_hSmD_hSmE_OR_hSmD_SfE, hSmD_hBE); 

  FuzzyRuleConsequent* then_VAD_AND_VSE = new FuzzyRuleConsequent();
  then_VAD_AND_VSE->addOutput(averageD);
  then_VAD_AND_VSE->addOutput(slowE);
 
  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, if_hSmD_hSmE_OR_hSmD_SfE__OR__hSmD_hBE, then_VAD_AND_VSE);
  fuzzy->addFuzzyRule(fuzzyRule2);  

  //*********           REGRA 3 para OUTPUT = averangeD AND slowE
  FuzzyRuleAntecedent* SfD_SfE = new FuzzyRuleAntecedent(); //1 a
  SfD_SfE -> joinWithAND(safeD,safeE);
  
  FuzzyRuleAntecedent* hBD_SfE = new FuzzyRuleAntecedent(); //1 a
  hBD_SfE -> joinWithAND(halfBigD,safeE);

  FuzzyRuleAntecedent* SfD_hBE = new FuzzyRuleAntecedent(); //2 a
  SfD_hBE -> joinWithAND(safeD,halfBigE);

  FuzzyRuleAntecedent* if_SfD_SfE_OR_hBD_SfE = new FuzzyRuleAntecedent();//1b
  if_SfD_SfE_OR_hBD_SfE ->joinWithOR(SfD_SfE, hBD_SfE); 

  FuzzyRuleAntecedent* if_SfD_SfE_OR_hBD_SfE__OR__SfD_hBE = new FuzzyRuleAntecedent();//1b
  if_SfD_SfE_OR_hBD_SfE__OR__SfD_hBE ->joinWithOR(if_SfD_SfE_OR_hBD_SfE, SfD_hBE); 

  FuzzyRuleConsequent* then_VAD_AND_VAE = new FuzzyRuleConsequent();
  then_VAD_AND_VAE->addOutput(averageD);
  then_VAD_AND_VAE->addOutput(averageE);
 
  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, if_SfD_SfE_OR_hBD_SfE__OR__SfD_hBE, then_VAD_AND_VAE);
  fuzzy->addFuzzyRule(fuzzyRule3);  

  
  //************* Regra 4 para OUTPUT = SlowD AND averageE

  FuzzyRuleAntecedent* SfD_hSmE = new FuzzyRuleAntecedent(); //1 a
  SfD_hSmE -> joinWithAND(safeD,halfSmallE);
  
  FuzzyRuleAntecedent* hBD_hSmE = new FuzzyRuleAntecedent(); //1 a
  hBD_hSmE -> joinWithAND(halfBigD,halfSmallE);

  FuzzyRuleAntecedent* if_SfD_hSmE_OR_hBD_hSmE = new FuzzyRuleAntecedent(); //1 b
  if_SfD_hSmE_OR_hBD_hSmE ->joinWithOR(SfD_hSmE, hBD_hSmE); 

  FuzzyRuleConsequent* then_VSD_AND_VAE = new FuzzyRuleConsequent();
  then_VSD_AND_VAE->addOutput(slowD);
  then_VSD_AND_VAE->addOutput(averageE);
 
  FuzzyRule* fuzzyRule4 = new FuzzyRule(4, if_SfD_hSmE_OR_hBD_hSmE, then_VSD_AND_VAE);
  fuzzy->addFuzzyRule(fuzzyRule4);  

//************* Regra 5 para OUTPUT = fastD AND averageE

  FuzzyRuleAntecedent* SfD_BE = new FuzzyRuleAntecedent(); //1 a
  SfD_BE -> joinWithAND(safeD,bigE);
  
  FuzzyRuleAntecedent* hBD_BE = new FuzzyRuleAntecedent(); //1 a
  hBD_BE -> joinWithAND(halfBigD,bigE);

  FuzzyRuleAntecedent* if_SfD_BE_OR_hBD_BE = new FuzzyRuleAntecedent(); //1 b
  if_SfD_BE_OR_hBD_BE ->joinWithOR(SfD_BE, hBD_BE); 

  FuzzyRuleConsequent* then_VFD_AND_VAE = new FuzzyRuleConsequent();
  then_VFD_AND_VAE->addOutput(fastD);
  then_VFD_AND_VAE->addOutput(averageE);
 
  FuzzyRule* fuzzyRule5 = new FuzzyRule(5, if_SfD_BE_OR_hBD_BE, then_VFD_AND_VAE);
  fuzzy->addFuzzyRule(fuzzyRule5);  

//************* Regra 6 para OUTPUT = averageD AND fastE

  FuzzyRuleAntecedent* BD_hBE = new FuzzyRuleAntecedent(); //1 a
  BD_hBE -> joinWithAND(bigD,halfBigE);
  
  FuzzyRuleAntecedent* BD_SfE = new FuzzyRuleAntecedent(); //1 a
  BD_SfE -> joinWithAND(bigD,safeE);

  FuzzyRuleAntecedent* if_BD_hBE_OR_BD_SfE = new FuzzyRuleAntecedent(); //1 b
  if_BD_hBE_OR_BD_SfE ->joinWithOR(BD_hBE, BD_SfE); 

  FuzzyRuleConsequent* then_VAD_AND_VFE = new FuzzyRuleConsequent();
  then_VAD_AND_VFE->addOutput(averageD);
  then_VAD_AND_VFE->addOutput(fastE);
 
  FuzzyRule* fuzzyRule6 = new FuzzyRule(6, if_BD_hBE_OR_BD_SfE, then_VAD_AND_VFE);
  fuzzy->addFuzzyRule(fuzzyRule6); 

  //************* Regra 7 para OUTPUT = fastD AND fastE

  FuzzyRuleAntecedent* BD_BE = new FuzzyRuleAntecedent(); //1 a
  BD_BE -> joinWithAND(bigD,bigE);
  
  FuzzyRuleAntecedent* hBD_hBE = new FuzzyRuleAntecedent(); //1 a
  hBD_hBE -> joinWithAND(halfBigD,halfBigE);

  FuzzyRuleAntecedent* if_BD_BE_OR_hBD_hBE = new FuzzyRuleAntecedent(); //1 b
  if_BD_BE_OR_hBD_hBE ->joinWithOR(BD_BE, hBD_hBE); 

  FuzzyRuleConsequent* then_VFD_AND_VFE = new FuzzyRuleConsequent();
  then_VFD_AND_VFE->addOutput(fastD);
  then_VFD_AND_VFE->addOutput(fastE);
 
  FuzzyRule* fuzzyRule7 = new FuzzyRule(7, if_BD_BE_OR_hBD_hBE, then_VFD_AND_VFE);
  fuzzy->addFuzzyRule(fuzzyRule7); 


  //***************** Regra 8 para OUTPUT = slowD AND fastE
  
  FuzzyRuleAntecedent* BD_hSmE = new FuzzyRuleAntecedent();
  BD_hSmE->joinWithAND(bigD,halfSmallE);
  
  FuzzyRuleConsequent* then_BD_hSmE = new FuzzyRuleConsequent(); 
  then_BD_hSmE->addOutput(slowD);
  then_BD_hSmE->addOutput(fastE);
 
  FuzzyRule* fuzzyRule8 = new FuzzyRule(8, BD_hSmE, then_BD_hSmE);
  fuzzy->addFuzzyRule(fuzzyRule8); 

   //Regra 9 para OUTPUT = fastD AND slowE
  
  FuzzyRuleAntecedent* hSmD_BE = new FuzzyRuleAntecedent();
  hSmD_BE->joinWithAND(halfSmallD,bigE);
  
  FuzzyRuleConsequent* then_hSmD_BE = new FuzzyRuleConsequent(); 
  then_hSmD_BE->addOutput(fastD);
  then_hSmD_BE->addOutput(slowE);
 
  FuzzyRule* fuzzyRule9 = new FuzzyRule(9, hSmD_BE, then_hSmD_BE);
  fuzzy->addFuzzyRule(fuzzyRule9); 

}
void ir_para_tras(int vel);
void ir_para_frente(int vel);
void ir_para_lado_esquerdo(int vel);
void ir_para_lado_direito(int vel);
void parado(int vel);

float ler_sensorE();
float ler_sensorD();

void loop() {
  
  fuzzy->setInput(1,ler_sensorE() );
  fuzzy->setInput(2,ler_sensorD() );

  fuzzy->fuzzify();
  int output1 = fuzzy->defuzzify(1);
  int output2 = fuzzy->defuzzify(2);
  
    Serial.print("Ecm: ");
    Serial.println(ler_sensorE());
    Serial.print("Dcm: ");
    Serial.println(ler_sensorD());
    Serial.print("Vel_1: ");
    Serial.println(output1);
    Serial.print("Vel_2: ");
    Serial.println(output2);
 
  if (output1 < 0){
        analogWrite(motor_1_a,-output1);
        analogWrite(motor_2_a,0); 
  }
  else{
        analogWrite(motor_2_a,output1);
        analogWrite(motor_1_a,0);
  }
  
  if (output2 < 0){
        analogWrite(motor_1_b,-output1);
        analogWrite(motor_2_b,0);
  }
  else{
        analogWrite(motor_2_b,output1);
        analogWrite(motor_1_b,0);
  }
}


void ir_para_tras(int vel){
  analogWrite(motor_1_b,vel);
  analogWrite(motor_1_a,vel);
  analogWrite(motor_2_b,0);
  analogWrite(motor_2_a,0);
}
void ir_para_frente(int vel){
  analogWrite(motor_2_b,vel);
  analogWrite(motor_2_a,vel);
}
void ir_para_lado_esquerdo(int vel){
  analogWrite(motor_2_a,0);
  analogWrite(motor_1_a,0);
  analogWrite(motor_2_b,vel);
  analogWrite(motor_1_b,0);
}
void ir_para_lado_direito(int vel){
  analogWrite(motor_1_b,0);
  analogWrite(motor_2_b,0);
  analogWrite(motor_2_a,vel);
  analogWrite(motor_1_a,0);
}
void parado(int vel){
  analogWrite(motor_1_b,0);
  analogWrite(motor_2_b,0);
  analogWrite(motor_2_a,0);
  analogWrite(motor_1_a,0);
}

float ler_sensorE(){
  float vlr_lido;
  digitalWrite(triggerE,HIGH);
  delayMicroseconds(50);
  digitalWrite(triggerE,LOW);
  vlr_lido=pulseIn(echoE,HIGH);//Tempo de sinal 
  return (vlr_lido/2 /29);//cm
}
  
float ler_sensorD(){
  float vlr_lido;
  digitalWrite(triggerD,HIGH);
  delayMicroseconds(50);
  digitalWrite(triggerD,LOW);
  vlr_lido=pulseIn(echoD,HIGH);//Tempo de sinal 
  return (vlr_lido/2 /29);//cm
}



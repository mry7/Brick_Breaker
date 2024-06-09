#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SevSeg.h>

#define yukarii_butttonuu 18   // Yukarı butonun bağlı olduğu pin
#define asagii_butttonuu 17 // Aşağı butonun bağlı olduğu pin
#define okeyy_butttonuu 16 // Enter butonunun bağlı olduğu pin

const int ledd_1_pinii = 11; // LED pin numarası 1
const int ledd_2_pinii = 12; // LED pin numarası 2
const int ledd_3_pinii = 13; // LED pin numarası 3

#define ekraninn_genisligii 128 // OLED ekran genişliği
#define ekraninn_yuksekligii 64 // OLED ekran yüksekliği

#define oledd_ekrann_resetii    -1
Adafruit_SSD1306 display(ekraninn_genisligii, ekraninn_yuksekligii, &Wire, oledd_ekrann_resetii);

#define paletinn_genisligii 30 // Palet genişliği
#define paletinn_yuksekligii 4 // Palet yüksekliği
#define paletinn_hiizii 4 // Palet hareket hızı
int pallett_x;


#define tuglaa_geniisligii 10 // Tuğla genişliği
#define tuglaa_yuksekliigii 4 // Tuğla yüksekliği
#define tuglalarr_arasii_boslukk 2 // Tuğla arası boşluk
int satiirr_sayiisii; // Tuğla satır sayısı
int sutuunn_sayiisii; // Tuğla sütun sayısı
#define tuglaninn_satirr_sayisii 10 // Define the number of rows for tuglalaarrr
#define tuglaninn_sutunn_sayisii 10// Define the number of columns for tuglalaarrr


#define maximumm_cann_sayisii 3 // Maksimum can sayısı
int cann_sayiisii = maximumm_cann_sayisii; // Oyuncunun can sayısı
bool ekstraa_cann_durumuu = false; // ekstra Canın aktif olup olmadığını takip eder
int ekstraa_cann_x, ekstraa_cann_y; // ekstra Canın konumu
const int ekstraa_cann_boyutt = 3; // ekstra Canın boyutu


int topunn_x_yonundekii_hareketii = -2; // Başlangıçta sola doğru hareket
int topunn_y_yonundekii_hareketii = -2; // Başlangıçta yukarı doğru hareket
#define topp_boyuttuu 4 // Top boyutu
int topunn_y_konumuu;
int topunn_x_konumuu; 


int leevveel = 1; // Oyun seviyesi

int skorr_puannii = 0; // Oyuncunun skoru

int isikk_sensoruu = A1; // Fotoğraf direnci sensörünün bağlı olduğu analog pin

int sonn_okunann_potansiyometree_degerii = 0; // Son okunan potansiyometre değeri

const int segmentt_1_pinlerrii[7] = {27, 29, 31, 33, 35, 37, 39};
const int katott_1_pinii = 0; 
const int segmentt_2_pinlerrii[7] = {41, 43, 45, 47, 49, 51, 53};
const int katott_2_pinii = 5; 

const byte rakamlaarr[10][7] = {
  {1,1,1,1,1,1,0}, 
  {0,1,1,0,0,0,0}, 
  {1,1,0,1,1,0,1}, 
  {1,1,1,1,0,0,1}, 
  {0,1,1,0,0,1,1}, 
  {1,0,1,1,0,1,1}, 
  {1,0,1,1,1,1,1}, 
  {1,1,1,0,0,0,0}, 
  {1,1,1,1,1,1,1}, 
  {1,1,1,1,0,1,1}  
};






bool oyunn_bayragii = false; // Oyunun başlayıp başlamadığını belirleyen bayrak
int menuu_seciimii = 1; // Menü seçeneğinin başlangıç ​​değeri


  void anaa_menuu_gosterr() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println("Oyun Secenekleri:");
  display.setCursor(10, 25);
  //baslat
   if (menuu_seciimii != 1) {
    display.print("> Baslat");
    display.setCursor(10, 40);
    display.println("  Cikis");
   }
  //cikis
   if (menuu_seciimii != 2) {
    display.setCursor(10, 25);
    display.print("  Baslat");
    display.setCursor(10, 40);
    display.println("> Cikis");
   }
   display.display();
}

void menuu_isaretlee() {
  int yukarii_buttonuu_bass = digitalRead(yukarii_butttonuu);
  int asagii_buttonuu_bass = digitalRead(asagii_butttonuu);
  int okeyy_buttonuu_bass = digitalRead(okeyy_butttonuu);

  // Yukarı butona basıldıysa ve menü seçimi 2 değilse, menü seçimini bir arttir
  if (yukarii_buttonuu_bass == LOW && menuu_seciimii != 2) {
    menuu_seciimii = 2; //baslat
    anaa_menuu_gosterr(); // Menüyü güncelle
  }

  // asagi butona basıldıysa ve menü seçimi 1 değilse, menü seçimini bir azalt
  if (asagii_buttonuu_bass == LOW && menuu_seciimii != 1) {
    menuu_seciimii = 1; //cikis
    anaa_menuu_gosterr(); // Menüyü güncelle
  }

  // Enter butonuna basıldıysa
  if (okeyy_buttonuu_bass == LOW) {
    //baslat ve oyun bayragini true yap
    if (menuu_seciimii == 2) {
      oyunn_bayragii = true;
    }
    //cikisa yonlendir
    else if (menuu_seciimii == 1) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(10, 10);
      display.println("    Oyunumuza ");
      display.println("    gosterdiginiz ");
      display.println("      ilgi icin ");
      display.println("    tesekkurler...");


      display.display();
      delay(7000);
      display.clearDisplay();
      display.display();

      digitalWrite(ledd_1_pinii, LOW);
      digitalWrite(ledd_2_pinii, LOW);
      digitalWrite(ledd_3_pinii, LOW);


      exit(0); // Programı sonlandır

      }
  }
}


bool tuglalaarrr[tuglaninn_satirr_sayisii][tuglaninn_sutunn_sayisii]; // Tuğlaların durumu

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 baslatilamadi."));
    for(;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();

  randomSeed(analogRead(0));

  // LED pinlerini çıkış olarak ayarla
  pinMode(ledd_1_pinii, OUTPUT); 
  pinMode(ledd_2_pinii, OUTPUT);
  pinMode(ledd_3_pinii, OUTPUT);

  // Başlangıçta LED'leri aç
  digitalWrite(ledd_1_pinii, HIGH);
  digitalWrite(ledd_2_pinii, HIGH);
  digitalWrite(ledd_3_pinii, HIGH);

  pinMode(isikk_sensoruu, INPUT); // Fotoğraf direnci sensörünü giriş olarak ayarla


  pinMode(yukarii_butttonuu, INPUT_PULLUP); // Yukarı butonu giriş olarak ayarla
  pinMode(asagii_butttonuu, INPUT_PULLUP); // Aşağı butonu giriş olarak ayarla
  pinMode(okeyy_butttonuu, INPUT_PULLUP); // Enter butonu giriş olarak ayarla

  // Tuğlaları başlangıçta oluştur
  for (int i = 0; i < tuglaninn_satirr_sayisii; i++) {
    for (int j = 0; j < tuglaninn_sutunn_sayisii; j++) {
      tuglalaarrr[i][j] = true;
    }
  }
  leevveel = 1;

  tuglaa_dizaynii();

  // Skoru ekrana yazdır
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(skorr_puannii);
  display.display();

  // 7 segment ekran için pinler çıkış olarak ayarlanır
  for (int i = 0; i < 7; i++) {
    pinMode(segmentt_1_pinlerrii[i], OUTPUT);
  }
  pinMode(katott_1_pinii, OUTPUT);

  // ikinci 7 segment ekran için pinler çıkış olarak ayarlanır
  for (int i = 0; i < 7; i++) {
    pinMode(segmentt_2_pinlerrii[i], OUTPUT);
  }
  pinMode(katott_2_pinii, OUTPUT);

  // Oyun başladığında paleti ekranın ortasına konumlandır
  pallett_x = (ekraninn_genisligii - paletinn_genisligii) / 2;

  // Potansiyometre değerini başlangıçta sabit tut
  sonn_okunann_potansiyometree_degerii = analogRead(A0);

  // Oyun başladığında topu paletin üstünde başlat
  topunn_x_konumuu = (ekraninn_genisligii - topp_boyuttuu) / 2;
  topunn_y_konumuu = ekraninn_yuksekligii - paletinn_yuksekligii - topp_boyuttuu;
  
}


void tuglaa_dizaynii() {
  display.clearDisplay(); // Ekrandaki önceki içeriği temizle

  switch (leevveel) {
    case 1:
      // Level 1: 10 sütun, 3 satır (piramit şeklinde)
      sutuunn_sayiisii = 10;
      satiirr_sayiisii = 5;
      break;
    case 2:
      // Level 2: 9 sütun, 5 satır (ters piramit şeklinde)
      sutuunn_sayiisii = 9;
      satiirr_sayiisii = 5;
      break;
    case 3:
      // Level 3: 9-10 sütun, 5 satır 
      sutuunn_sayiisii = 10;
      satiirr_sayiisii = 5;
      break;
    case 4:
      // Level 4: 5 sütun, 5 satır
      sutuunn_sayiisii = 5;
      satiirr_sayiisii = 5;
      break;
    case 5:
      // Level 5: 8 sütun, 8 satır
      sutuunn_sayiisii = 8;
      satiirr_sayiisii = 8;
      break;
    default:
    // bu verilen sayıların dışında bir seviye olursa default olur 
    // Her bir seviye için sütun ve satır sayısı farklıdır.
    // Seviye arttıkça sütun ve satır sayıları artar.
    // Örneğin, 6. seviye için sütun sayısı 9 + (6-1) * 2 = 15, satır sayısı ise 1 + (6-1) = 6 olacaktır.
      sutuunn_sayiisii = 5 + (leevveel - 1) * 2;
      satiirr_sayiisii = 1 + (leevveel - 1);
      break;
  
  }

   // Eğer leevveel 1'den büyükse, seviye bilgisini ekranda göster
  if (leevveel > 1) {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10, ekraninn_yuksekligii / 2 - 10);
    display.print("Level ");
    display.println(leevveel);
    display.display();
    
    // Ekranda 5 saniye beklet
    delay(5000);
  }

// Tuğla düzenini ekrana yazdır

 //düz piramit
if (leevveel == 1) { // Sadece birinci seviye için geçerlidir
  int tuglaa_sayiisii = 1; // Başlangıçta bir tuğla ile başlar
  int tuglaa_baslangicc_indexii = (tuglaninn_sutunn_sayisii - tuglaa_sayiisii) / 2; // Her satırda tuğlaların başlangıç indeksi, tuğlaların ortalanması için hesaplanır
  
  // Her satırı dolaşır
  for (int i = 0; i < tuglaninn_satirr_sayisii; ++i) {
    int tuglaa_bitiss_indexii = tuglaa_baslangicc_indexii + tuglaa_sayiisii; // Her satırda tuğlaların bitiş indeksi hesaplanır
    // Her sütunu dolaşır
    for (int j = 0; j < tuglaninn_sutunn_sayisii; ++j) {
      // Eğer sütun, tuğlaların başlangıç ve bitiş indeksi arasında ise o sütunda tuğla vardır
      if (j >= tuglaa_baslangicc_indexii && j < tuglaa_bitiss_indexii) {
        tuglalaarrr[i][j] = true; // Tuğla vardır
      } else {
        tuglalaarrr[i][j] = false; // Tuğla yoktur
      }
    }
    tuglaa_sayiisii += 2; // Bir sonraki satırda tuğla sayısı iki artar
    tuglaa_baslangicc_indexii = (tuglaninn_sutunn_sayisii - tuglaa_sayiisii) / 2; // Yeni satırın tuğla başlangıç indeksi hesaplanır
  }
}


//ters piramit
if (leevveel == 2) { // Sadece ikinci seviye için geçerlidir
  int tuglaa_sayiisii = tuglaninn_sutunn_sayisii; // İlk satırda sütun sayısı kadar tuğla ile başlar
  // Her satırı dolaşır
  for (int i = 0; i < tuglaninn_satirr_sayisii; ++i) {
    int tuglaa_baslangicc_indexii = (tuglaninn_sutunn_sayisii - tuglaa_sayiisii) / 2; // Her satırda tuğlaların başlangıç indeksi, tuğlaların ortalanması için hesaplanır
    int tuglaa_bitiss_indexii = tuglaa_baslangicc_indexii + tuglaa_sayiisii; // Her satırda tuğlaların bitiş indeksi hesaplanır
    // Her sütunu dolaşır
    for (int j = 0; j < tuglaninn_sutunn_sayisii; ++j) {
      // Eğer sütun, tuğlaların başlangıç ve bitiş indeksi arasında ise o sütunda tuğla vardır
      if (j >= tuglaa_baslangicc_indexii && j < tuglaa_bitiss_indexii) {
        tuglalaarrr[i][j] = true; // Tuğla vardır
      } else {
        tuglalaarrr[i][j] = false; // Tuğla yoktur
      }
    }
    tuglaa_sayiisii -= 2; // Bir sonraki satırda tuğla sayısı iki azalır
  }
}


// Üçüncü seviye için tuğla dizilimi oluşturulur
if (leevveel == 3) {
  for (int i = 0; i < 5; i++) { // Satırların sayısı 5 olarak sabittir
    for (int j = 0; j < 9 - i; j++) { // Sütun sayısı, her satır için azalır
      tuglalaarrr[i][j] = true; // Tuğla var
    }
  }
}

// Dördüncü seviye için tuğla dizilimi oluşturulur
if (leevveel == 4) {
  for (int i = 0; i < tuglaninn_satirr_sayisii; i++) { // Tüm satırlar gezilir
    for (int j = 0; j < tuglaninn_sutunn_sayisii; j++) { // Tüm sütunlar gezilir
      tuglalaarrr[i][j] = true; // Tuğla var
    }
  }
}

// Beşinci seviye için tuğla dizilimi oluşturulur
if (leevveel == 5) {
  for (int i = 0; i < 8; i++) { // Satırların sayısı 8 olarak sabittir
    for (int j = 0; j < 8 - i; j++) { // Sütun sayısı, her satır için azalır
      tuglalaarrr[i][j] = true; // Tuğla var
    }
  }
}

// Tuğla sayısı, seviyeye göre sınırlandırılır
sutuunn_sayiisii = min(sutuunn_sayiisii, tuglaninn_sutunn_sayisii); // Sütun sayısı, tuğla diziliminin sütun sayısından fazla olamaz
satiirr_sayiisii = min(satiirr_sayiisii, tuglaninn_satirr_sayisii); // Satır sayısı, tuğla diziliminin satır sayısından fazla olamaz

}





void loop() {
  if (!oyunn_bayragii) {
    anaa_menuu_gosterr();
    menuu_isaretlee();
  } else {
    display.clearDisplay();

    // Fotoğraf direnci sensöründen okunan değeri al
    int isikk_sensoruu_degerii = analogRead(isikk_sensoruu);

    // Arka plan rengini belirle
    uint16_t arkaa_plann_rengiii = isikk_sensoruu_degerii > 500 ? WHITE : BLACK;

    // Arka planı güncelle
    display.fillScreen(arkaa_plann_rengiii);

    // Tuğlaları, paleti ve topu arka plan renginin tersine göre çiz
    uint16_t tuglaa_rengiii = arkaa_plann_rengiii == BLACK ? WHITE : BLACK;
    uint16_t palett_rengiii = arkaa_plann_rengiii == BLACK ? WHITE : BLACK;
    uint16_t topp_rengiii = arkaa_plann_rengiii == BLACK ? WHITE : BLACK;
    // ekstra can  rengi
    uint16_t ekstraaCann_rengiii = arkaa_plann_rengiii == BLACK ? WHITE : BLACK;

    // Tuğlaları çiz
    for (int i = 0; i < satiirr_sayiisii; i++) {
      for (int j = 0; j < sutuunn_sayiisii; j++) {
        if (tuglalaarrr[i][j]) {
          // Tuğlayı çiz
          display.fillRect(j * (tuglaa_geniisligii + tuglalarr_arasii_boslukk), i * (tuglaa_yuksekliigii + tuglalarr_arasii_boslukk), tuglaa_geniisligii, tuglaa_yuksekliigii, tuglaa_rengiii);
        }
      }
    }

    // Paleti çiz
    display.fillRect(pallett_x, ekraninn_yuksekligii - paletinn_yuksekligii, paletinn_genisligii, paletinn_yuksekligii, palett_rengiii);

    // Topu çiz
    display.fillCircle(topunn_x_konumuu, topunn_y_konumuu, topp_boyuttuu, topp_rengiii);

    // Potansiyometrenin değerini oku ve paleti güncelle
    int potansiyometree_degeriii = analogRead(A0);
    // Yön, mevcut potansiyometre değeri ile önceki değer arasındaki farktır.
    int yonnn = potansiyometree_degeriii - sonn_okunann_potansiyometree_degerii;
    // Önceki potansiyometre değerini günceller.
    sonn_okunann_potansiyometree_degerii = potansiyometree_degeriii;

    // Paletin x konumunu günceller. Yön değeri, potansiyometrenin değişimine bağlıdır. 
    // Ancak, palet ekranın sınırlarını aşmamalıdır.Bu nedenle constrain() fonksiyonu kullanılarak
    // paletin x konumu, ekranın genişliği ve paletin genişliği arasında sınırlanır.
    pallett_x = constrain(pallett_x + yonnn * paletinn_hiizii, 0, ekraninn_genisligii - paletinn_genisligii);

    // Topun hareketini güncelle
    // Topun x konumunu, belirlenen yönde hareket miktarı kadar günceller.
    topunn_x_konumuu += topunn_x_yonundekii_hareketii;
    // Topun y konumunu, belirlenen yönde hareket miktarı kadar günceller.
    topunn_y_konumuu += topunn_y_yonundekii_hareketii;
     
    // Topun çarpışmalarını kontrol et

    //______________________ sag veya sol ___________________________
    // Eğer top ekranın sol veya sağ kenarına çarparsa, x yönlü hareketini tersine çevirir.
    if (topunn_x_konumuu <= 0 || topunn_x_konumuu >= ekraninn_genisligii) {
      topunn_x_yonundekii_hareketii *= -1;
    }

    //______________________ tavan ___________________________
    //tavana çarpma durumu
    // Eğer top ekranın üst kenarına çarparsa
    // Yönü tersine çevirerek aşağıya doğru devam eder.
    if (topunn_y_konumuu <= 0) {
      // Yönü tersine çevir
      topunn_y_yonundekii_hareketii = abs(topunn_y_yonundekii_hareketii);
    }

    //______________________ taban ___________________________
     // Eğer top ekranın alt kenarına çarparsa
     //iki durum var 1.si palete çarpar ve seker , 2.yere düşer ve can kaybeder
      if (topunn_y_konumuu >= ekraninn_yuksekligii - topp_boyuttuu) {

      //ilk durum (palete çarpıp seker)
      if (topunn_x_konumuu >= pallett_x && topunn_x_konumuu <= pallett_x + paletinn_genisligii) {
        // Eğer top paletin üzerine düşerse, yukarı yöne hareket eder.(top paletten seker)
        //yönü tersine çeviriyoruz (asagi dogru duserken paletten sekip yukari hareket etmeye baslar)
        topunn_y_yonundekii_hareketii *= -1;
      } else {

        //ikinci durum (yer düşer ve can kaybeder)
        // Eğer top paletin üzerine düşmezse, topu ekranın ortasına geri konumlandırır.
        // Can sayısını azaltır ve LED durumunu günceller.
        topunn_x_konumuu = ekraninn_genisligii / 2;
        topunn_y_konumuu = ekraninn_yuksekligii / 2;
        cann_sayiisii--; // Can sayısını azaltır.
        ledd_durumunuu_guncellee(); // LED durumunu günceller.
        delay(1000);
      }
    }

    // Tuğla çarpışmalarını kontrol et
 bool tumm_tuglalarr_kirildii_mii = true; // Tüm tuğlaların kırılıp kırılmadığını kontrol etmek için bir bayrak
for (int i = 0; i < satiirr_sayiisii; i++) { // Satırları gezer
  for (int j = 0; j < sutuunn_sayiisii; j++) { // Sütunları gezer
    if (tuglalaarrr[i][j]) { // Eğer tuğla varsa
      tumm_tuglalarr_kirildii_mii = false; // Bayrağı false yap, çünkü en az bir tuğla var
      int tuglaa_x = j * (tuglaa_geniisligii + tuglalarr_arasii_boslukk); // Tuğlanın x konumu
      int tuglaa_y = i * (tuglaa_yuksekliigii + tuglalarr_arasii_boslukk); // Tuğlanın y konumu
      if (topunn_x_konumuu + topp_boyuttuu >= tuglaa_x && topunn_x_konumuu <= tuglaa_x + tuglaa_geniisligii && topunn_y_konumuu + topp_boyuttuu >= tuglaa_y && topunn_y_konumuu <= tuglaa_y + tuglaa_yuksekliigii) {
        // Eğer top tuğlaya çarparsa
        topunn_y_yonundekii_hareketii *= -1; // Topun yönünü tersine çevirerek yukarı doğru devam etmesini sağlar
        tuglalaarrr[i][j] = false; // Çarpılan tuğlayı kırılmış olarak işaretler
        skoruu_arttirr(); // Skoru artırır
        // Eğer ekstra can paketi aktif değilse ve %10 olasılık sağlanıyorsa
        if (!ekstraa_cann_durumuu && random(100) < 10) {
          ekstraa_cann_durumuu = true; // Ekstra can paketini aktif hale getirir
          // Can paketinin X konumunu tuğlanın ortasına ayarlar
          ekstraa_cann_x = tuglaa_x + tuglaa_geniisligii / 2 - ekstraa_cann_boyutt / 2;
          // Can paketinin Y konumunu tuğlanın ortasına ayarlar
          ekstraa_cann_y = tuglaa_y + tuglaa_yuksekliigii / 2 - ekstraa_cann_boyutt / 2;
        }
      }
    }
  }
}

// Can paketini çiz
if (ekstraa_cann_durumuu) { // Eğer ekstra can paketi aktif olduysa
  ekstraa_cann_y += 1; // Düşme hızı
    // ekstra can paketi  çizer
  display.fillCircle(ekstraa_cann_x, ekstraa_cann_y, ekstraa_cann_boyutt, ekstraaCann_rengiii); // Süper can paketini çiz

  // Palet ile can paketinin teması
  // Eğer ekstra can paketinin y konumu (yükseklik) paletin yüksekliğinin üstünde 
  //ve x konumu (yatay konum) paletin içindeyse can alinmis sayilsin
  if (ekstraa_cann_y >= ekraninn_yuksekligii - paletinn_yuksekligii && ekstraa_cann_x >= pallett_x && ekstraa_cann_x <= pallett_x + paletinn_genisligii) {
    if (cann_sayiisii < maximumm_cann_sayisii) { // Eğer maksimum can sayısına ulaşılmadıysa
      cann_sayiisii++; // Canı artır
      // LED'leri manuel olarak yak
      if (cann_sayiisii == 1) {
        digitalWrite(ledd_3_pinii, HIGH); // Birinci LED'i yak
      } else if (cann_sayiisii == 2) {
        digitalWrite(ledd_2_pinii, HIGH); // İkinci LED'i yak
      } else if (cann_sayiisii == 3) {
        digitalWrite(ledd_1_pinii, HIGH); // Üçüncü LED'i yak
      }
    }
    ekstraa_cann_durumuu = false; // Paketi kaldır
  } else if (ekstraa_cann_y > ekraninn_yuksekligii) {
    ekstraa_cann_durumuu = false; // Ekrandan çıkarsa paketi kaldır
  }
}

    // Eğer tüm tuğlalar kırıldıysa ve oyun bitmediyse, diğer seviyeye geç
    if (tumm_tuglalarr_kirildii_mii && cann_sayiisii > 0) {
      leevveel++; // Seviye numarasını artır
      tuglaa_dizaynii();
      // Topu ortaya yerleştir
      topunn_x_konumuu = ekraninn_genisligii / 2 - topp_boyuttuu / 2; 
      topunn_y_konumuu = ekraninn_yuksekligii - paletinn_yuksekligii - topp_boyuttuu;
      //plaeti ortaya yerleştir
      pallett_x = (ekraninn_genisligii - paletinn_genisligii) / 2;

      display.clearDisplay(); // Ekranı temizle
      
      // Her seviyede topun hızını %20 artır
      topunn_x_yonundekii_hareketii *= 1.20;
      topunn_y_yonundekii_hareketii *= 1.20;

    }

    // Skoru ekrana yazdır
    // Skor rengini belirle
    uint16_t skorr_rengiii = arkaa_plann_rengiii == BLACK ? WHITE : BLACK;

    // Skoru ekrana yazdır
    display.setTextSize(1);
    display.setTextColor(skorr_rengiii);
    display.setCursor(0, 0);
    display.print("Score: ");
    display.print(skorr_puannii);
    display.display();

    // Skoru her saniye bir kez yedi segment ekranlara yazdır
    // Önceki skor güncelleme zamanını saklamak için kullanılan değişken
    static unsigned long enn_sonn_olculenn_zamnn = 0;
    // Şu anki zamanı alır
    unsigned long suannn = millis();

// Bir saniyeden fazla zaman geçmişse, skoru güncelle
if (suannn - enn_sonn_olculenn_zamnn >= 1000) {
  // Onlar basamağındaki skoru yedi segment ekranında göster
  yedii_segmentt_skoruu_gosterr(skorr_puannii / 10, segmentt_1_pinlerrii, katott_1_pinii);

  // Birler basamağındaki skoru yedi segment ekranında göster
  yedii_segmentt_skoruu_gosterr(skorr_puannii % 10, segmentt_2_pinlerrii, katott_2_pinii);

  // Son skor güncelleme zamanını şu anki zaman olarak ayarla
  enn_sonn_olculenn_zamnn = suannn;
}

    // Oyunun bitip bitmediğini kontrol et
    if (cann_sayiisii <= 0) {
      oyunn_bitttiii();
    }

    delay(10);
  }
}



void yedii_segmentt_skoruu_gosterr(int sayiii, const int segmentt_pinleriii[], int ortakk_katott) {

 // Eğer sayı 9'dan büyükse, ekrana 1 gösterilecek.
  if (sayiii > 9) {
    sayiii = 1;
  }

  // 7 segment ekranın her bir segment pinine, sayının gösterilmesi için gerekli olan değerler
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentt_pinleriii[i], rakamlaarr[sayiii][i]);
  }
  // Ortak katot pinine LOW değeri verilerek ekran kapatılıyor.
  digitalWrite(ortakk_katott, LOW);
}


void skoruu_arttirr() {
  skorr_puannii++; 
}

// Can sayısına göre LED'leri güncelle
void ledd_durumunuu_guncellee() {
    // Eğer can sayısı 2 ise, ilk LED'i kapat
  if (cann_sayiisii == 2) {
    digitalWrite(ledd_1_pinii, LOW);
    // Eğer can sayısı 1 ise, ikinci LED'i kapat
  } else if (cann_sayiisii == 1) {
    digitalWrite(ledd_2_pinii, LOW);
    // Eğer can sayısı 0 ise, üçüncü LED'i kapat ve oyunu bitir
  } else if (cann_sayiisii == 0) {
    digitalWrite(ledd_3_pinii, LOW);
    oyunn_bitttiii();
  }

   // Yeni bir can kaybedildiğinde
  if (cann_sayiisii > 0) {
    // Paleti ekranın ortasına konumlandır
    pallett_x = (ekraninn_genisligii - paletinn_genisligii) / 2;

    // Topu paletin üstünde başlat

   // Topun x konumunu ayarla:
   // Paletin x konumuna, paletin genişliğinin yarısı eklenir (paletin merkezi),
   // Ardından topun genişliğinin yarısı çıkarılarak topun merkezi paletin merkezine getirilir.
   topunn_x_konumuu = pallett_x + paletinn_genisligii / 2 - topp_boyuttuu / 2;

   // Topun y konumunu ayarla:
   // Ekranın yüksekliğinden paletin yüksekliği ve topun yüksekliği çıkarılarak
   // topun ekranın üstünde ve paletin üstünde başlayacağı yükseklik belirlenir.
   topunn_y_konumuu = ekraninn_yuksekligii - paletinn_yuksekligii - topp_boyuttuu;
}
}

// Oyunu bitir
void oyunn_bitttiii() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, ekraninn_yuksekligii / 2 - 10);
  display.println("Game Over");
  display.setCursor(20, ekraninn_yuksekligii / 2 + 10);
  display.print("Score: ");
  display.print(skorr_puannii);
  display.display();

  

  delay(3000);
  display.clearDisplay();

  // Oyunun bitiminde oyuncuya tekrar oynamak isteyip istemediği sorulur
  tekrarr_oynaa();

}

void tekrarr_oynaa() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println("Oyun Secenekleri:");
  display.setCursor(10, 25);
  display.println("1.  BASLAT");
  display.setCursor(10, 40);
  display.print("2.  CIKIS");
  display.display();

  int seciimm = 0;
  while (true) {
      //baslat
    if (digitalRead(yukarii_butttonuu) == LOW) {
      seciimm = 1;
      break;
      //cikis
    } else if (digitalRead(asagii_butttonuu) == LOW) {
      seciimm = 2;
      break;
    }
    delay(100);
  }

  if (seciimm == 1) {
    // Tekrar oynamak istenirse
    oyunn_bayragii = true;
    leevveel = 1;
    cann_sayiisii = maximumm_cann_sayisii;
    skorr_puannii = 0;
    topunn_x_yonundekii_hareketii = -2; // X yönünü başlangıç değerine döndür
    topunn_y_yonundekii_hareketii = -2; // Y yönünü başlangıç değerine döndür    
    tuglaa_dizaynii();
    // Topu paletin üstünde başlat
    topunn_x_konumuu = ekraninn_genisligii / 2 - topp_boyuttuu / 2;
    topunn_y_konumuu = ekraninn_yuksekligii - paletinn_yuksekligii - topp_boyuttuu;
    // LED'leri yeniden aktif et
    digitalWrite(ledd_1_pinii, HIGH);
    digitalWrite(ledd_2_pinii, HIGH);
    digitalWrite(ledd_3_pinii, HIGH);
  } else {
    // Oyunu sonlandır
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(10, 10);
      display.println("    Oyunumuza ");
      display.println("    gosterdiginiz ");
      display.println("      ilgi icin ");
      display.println("    tesekkurler...");


      display.display();
      delay(7000);
      display.clearDisplay();
      display.display();

      digitalWrite(ledd_1_pinii, LOW);
      digitalWrite(ledd_2_pinii, LOW);
      digitalWrite(ledd_3_pinii, LOW);


      exit(0); // Programı sonlandır


  }
}



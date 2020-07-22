#include <stdio.h>

void main();
void arac_ekle();
void arac_listele();
void arac_ara();
void arac_sil();
int cikis(int islem);
void musteri_ekle();
void musteri_listele();
void musteri_ara();
void musteri_sil();
void kirala();
void iade();

struct arac
{
    int musait;
    int plaka, ucret;
    char model[50], renk[50];
};

struct musteri
{
    int musteri_no;
    char soyisim[50], isim[50], memleket[50];
};

struct kiralama
{
    int plaka, musteri_no;
    char kiralama_tarihi[10], iade_tarihi[10];
};

void arac_ekle(){
    FILE *farac;

    struct arac yeni_arac;

    printf("Arac bilgilerini girin: \nPlaka: ");
    scanf("%d", &yeni_arac.plaka);

    printf("Renk: ");
    scanf("%s", yeni_arac.renk);

    printf("Model: ");
    scanf("%s", yeni_arac.model);

    printf("Ucret: ");
    scanf("%d", &yeni_arac.ucret);

    printf("Musaitlik: ");
    scanf("%i", &yeni_arac.musait);

    farac = fopen("arac.txt", "a+");
    fprintf(farac, "%d | %s | %s | %d | %d\n", yeni_arac.plaka, yeni_arac.renk, yeni_arac.model, yeni_arac.ucret, yeni_arac.musait);
    fclose(farac);
    printf("\nArac kayit edildi.\n");

}

void arac_listele(){

    FILE *farac = fopen("arac.txt", "r");

    struct arac araclar;
    char a;

    if ((a = getc(farac)) == EOF){
        printf("Listelenecek arac bulunamadi.");
    } else{
        rewind(farac);
        printf("\n\n%-10s | %-10s | %-15s | %-7s | %-15s |\n", "Plaka", "Renk", "Model", "Ucret", "Musaitlik");
        printf("-----------|------------|-----------------|---------|-----------------|\n");
        fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait); 
    }

    while ((a = getc(farac)) != EOF)
    {
        printf("%-10d | %-10s | %-15s | %-7d | %-15d |\n", araclar.plaka, araclar.renk, araclar.model, araclar.ucret, araclar.musait);    
        fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait); 
    }
    
    fclose(farac);
}

void arac_ara(){

    FILE *farac = fopen("arac.txt", "r");

    struct arac araclar;
    char a;
    int aranacak_plaka, bulundu;

    printf("Aramak istediginiz aracin plakasini girin: ");
    scanf("%d", &aranacak_plaka);

    fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait);

    while ((a = getc(farac)) != EOF)
    {
        if(aranacak_plaka == araclar.plaka){
            printf("\n\n%-10s | %-10s | %-15s | %-7s | %-15s |\n", "Plaka", "Renk", "Model", "Ucret", "Musaitlik");
            printf("-----------|------------|-----------------|---------|-----------------|\n");
            printf("%-10d | %-10s | %-15s | %-7d | %-15d |\n", araclar.plaka, araclar.renk, araclar.model, araclar.ucret, araclar.musait);
            bulundu = 1;
            break;
        }  else {
            fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait);
            bulundu = 0;
        }
    }

    if (bulundu == 0)
        printf("Boyle bir arac yok.\n");

    fclose(farac);

}

void arac_sil(){
    FILE *farac_copy = fopen("arac_copy.txt", "w+"), *farac = fopen("arac.txt", "r");

    struct arac araclar;

    int silindi = 0, silinecek_plaka;
    char a;

    printf("Silmek istediginiz arac plakasini girin: ");
    scanf("%d", &silinecek_plaka);

    
    fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait);
    while ((a = getc(farac)) != EOF)
    {
        if (silinecek_plaka != araclar.plaka){
            fprintf(farac_copy, "%d | %s | %s | %d | %d\n", araclar.plaka, araclar.renk, araclar.model, araclar.ucret, araclar.musait);
        } else {
            silindi = 1;
        }
        fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait);
    }

    remove("arac.txt");
    rename("arac_copy.txt", "arac.txt");

    if (silindi == 1){
        printf("\nArac basarıyla silindi.\n");
    } else {
        printf("\nBu plakaya ait arac yok.\n");
    }

    fclose(farac_copy);
    fclose(farac);

}

int cikis(int islem){
    return (islem == 4) ? 1 : 0;
}

void musteri_ekle(){
    FILE *fmusteri;

    struct musteri yeni_musteri;

    printf("\nMusteri bilgilerini girin: \nMusteri Numarasi: ");
    scanf("%d", &yeni_musteri.musteri_no);

    printf("Isim: ");
    scanf("%s", yeni_musteri.isim);

    printf("Soyisim: ");
    scanf("%s", yeni_musteri.soyisim);

    printf("Memleket: ");
    scanf("%s", yeni_musteri.memleket);

    

    fmusteri = fopen("musteri.txt", "a+");
    fprintf(fmusteri, "%d | %s | %s | %s\n", yeni_musteri.musteri_no, yeni_musteri.isim, yeni_musteri.soyisim, yeni_musteri.memleket);
    fclose(fmusteri);
    printf("\nMusteri kayit edildi.\n");

    
}

void musteri_listele(){
    
    FILE *fmusteri = fopen("musteri.txt", "r+");

    struct musteri musterilar;
    char a;

    if ((a = getc(fmusteri)) == EOF){
        printf("Listelenecek musteri bulunamadi.");
    } else{
        rewind(fmusteri);
        printf("\n\n%-7s | %-15s | %-15s | %-15s |\n", "Numara", "Isim", "Soyisim", "Memleket");
        printf("--------|-----------------|-----------------|-----------------|\n");
        fscanf(fmusteri, "%d | %s | %s | %s", &musterilar.musteri_no, musterilar.isim, musterilar.soyisim, musterilar.memleket);
    }

    while ((a = getc(fmusteri)) != EOF)
    {
        printf("%-7d | %-15s | %-15s | %-15s |\n", musterilar.musteri_no, musterilar.isim, musterilar.soyisim, musterilar.memleket);    
        fscanf(fmusteri, "%d | %s | %s | %s", &musterilar.musteri_no, musterilar.isim, musterilar.soyisim, musterilar.memleket);    
    }
    
    fclose(fmusteri);
    
}

void musteri_ara(){

    FILE *fmusteri = fopen("musteri.txt", "r");

    struct musteri musteriler;
    char a;
    int aranacak_musteri_no, bulundu;

    printf("Aramak istediginiz Musteri Numarasini girin: ");
    scanf("%d", &aranacak_musteri_no);

    fscanf(fmusteri, "%d | %s | %s | %s", &musteriler.musteri_no, musteriler.isim, musteriler.soyisim, musteriler.memleket);

    while ((a = getc(fmusteri)) != EOF)
    {
        if(aranacak_musteri_no == musteriler.musteri_no){
            printf("\n\n%-7s | %-15s | %-15s | %-15s |\n", "Numara", "Isim", "Soyisim", "Memleket");
            printf("--------|-----------------|-----------------|-----------------|\n");
            printf("%-7d | %-15s | %-15s | %-15s |\n", musteriler.musteri_no, musteriler.isim, musteriler.soyisim, musteriler.memleket);
            bulundu = 1;
            break;
        } else {
            fscanf(fmusteri, "%d | %s | %s | %s", &musteriler.musteri_no, musteriler.isim, musteriler.soyisim, musteriler.memleket);
            bulundu = 0;
        }
    }

    if (bulundu == 0)
        printf("Böyle bir musteri yok.\n");

    fclose(fmusteri);

    
}

void musteri_sil(){
    FILE *fmusteri_copy = fopen("musteri_copy.txt", "w+"), *fmusteri = fopen("musteri.txt", "r");

    struct musteri musteriler;
    char a;
    int silinecek_no, silindi = 0;

    printf("Silmek istediginiz Musteri Numarasini girin: ");
    scanf("%d", &silinecek_no);

    fscanf(fmusteri, "%d | %s | %s | %s", &musteriler.musteri_no, musteriler.isim, musteriler.soyisim, musteriler.memleket);

    while ((a = getc(fmusteri)) != EOF)
    {
        if (silinecek_no != musteriler.musteri_no){
            fprintf(fmusteri_copy, "%d | %s | %s | %s\n", musteriler.musteri_no, musteriler.isim, musteriler.soyisim, musteriler.memleket);
        } else {
            silindi = 1;
        }
        fscanf(fmusteri, "%d | %s | %s | %s", &musteriler.musteri_no, musteriler.isim, musteriler.soyisim, musteriler.memleket);
    }

    remove("musteri.txt");
    rename("musteri_copy.txt", "musteri.txt");

    if (silindi == 1){
        printf("\nMusteri basariyla silindi.\n");
    } else {
        printf("\nBu numaraya sahib musteri yok.\n");
    }

    fclose(fmusteri_copy);
    fclose(fmusteri);

    
}

void kirala(){
    FILE *fkirala, *farac, *farac_copy;

    struct kiralama kiralama;
    struct arac araclar;
    char a;
    int bulundu = 0, musaitlik = 0;

    printf("\nKiralama bilgilerini girin: \nPlaka: ");
    scanf("%d", &kiralama.plaka);

    printf("Musteri Numarasi: ");
    scanf("%d", &kiralama.musteri_no);

    printf("Kiralama Tarihi (gg.aa.yy): ");
    scanf("%s", kiralama.kiralama_tarihi);

    
    farac = fopen("arac.txt", "r+");
    farac_copy = fopen("arac_copy.txt", "w+");
 

    if ((a = getc(farac)) == EOF){
        printf("Bu dosya bos\n");
    } else{
        rewind(farac);
        fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait); 
    }

    while ((a = getc(farac)) != EOF)
    {
        if(kiralama.plaka == araclar.plaka){
            musaitlik = araclar.musait;
            bulundu = 1;
            break;
        }  else {
            fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait);
            bulundu = 0;
        }
    }

    if (bulundu == 0)
        printf("Boyle bir arac yok.\n");
    

    if (musaitlik == 1){

        fkirala = fopen("kirala.txt", "a+");

        fprintf(fkirala, "%d | %d | %s | %s\n", kiralama.plaka, kiralama.musteri_no, kiralama.kiralama_tarihi, "0.0.0");
        
        rewind(farac);
        
        fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait);
        while (!feof(farac))
        {
            if (kiralama.plaka == araclar.plaka){
                araclar.musait = 0;
            }

            fprintf(farac_copy, "%d | %s | %s | %d | %d\n", araclar.plaka, araclar.renk, araclar.model, araclar.ucret, araclar.musait);
            fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait);
        }

        remove("arac.txt");
        rename("arac_copy.txt", "arac.txt");

        fclose(fkirala);

        printf("\n%d plakali araci kiraladiniz.\n", kiralama.plaka);
    } else {
        printf("Bu arac musait degil\n");
    }

    
    fclose(farac);
    fclose(farac_copy);
    remove("arac_copy.txt");

    
}

void iade(){
    FILE *fkirala, *farac, *fcopy;

    struct kiralama iade, kiralama;
    struct arac araclar;
    char a;
    int bulundu = 0, gun1, gun2, ay1, ay2, yil1, yil2, ucret = 0, fiyat;


    printf("\nIade bilgilerini girin: \nPlaka: ");
    scanf("%d", &iade.plaka);

    printf("Iade Tarihi (gg.aa.yy): ");
    scanf("%s", iade.iade_tarihi);

    fcopy = fopen("kirala_copy.txt", "w+");
    fkirala = fopen("kirala.txt", "r+");   

    if(!feof(fkirala)){

        fscanf(fkirala, "%d | %d | %s | %s", &kiralama.plaka, &kiralama.musteri_no, kiralama.kiralama_tarihi, kiralama.iade_tarihi);  
        while (!feof(fkirala))
        {
            fprintf(fcopy, "%d | %d | %s | %s\n", kiralama.plaka, kiralama.musteri_no, kiralama.kiralama_tarihi, (iade.plaka == kiralama.plaka) ? iade.iade_tarihi : kiralama.iade_tarihi);  
            fscanf(fkirala, "%d | %d | %s | %s", &kiralama.plaka, &kiralama.musteri_no, kiralama.kiralama_tarihi, kiralama.iade_tarihi);  
        }

        remove("kirala.txt");
        rename("kirala_copy.txt", "kirala.txt");

        printf("\n%d plakali araci iade ettiniz.\n", iade.plaka);
    } else {
        printf("Bu dosya boş.\n");
    }

    fclose(fkirala);
    fclose(fcopy);
    remove("kirala_copy.txt");

    farac = fopen("arac.txt", "r+");
    fcopy = fopen("arac_copy.txt", "w+");

    if(!feof(farac)){

        fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait);  
        while (!feof(farac))
        {
            fprintf(fcopy, "%d | %s | %s | %d | %d\n", araclar.plaka, araclar.renk, araclar.model, araclar.ucret, (iade.plaka == araclar.plaka) ? 1 : araclar.musait);  
            fiyat = (iade.plaka == araclar.plaka) ? araclar.ucret : fiyat;
            fscanf(farac, "%d | %s | %s | %d | %d", &araclar.plaka, araclar.renk, araclar.model, &araclar.ucret, &araclar.musait); 
        }

        remove("arac.txt");
        rename("arac_copy.txt", "arac.txt");
    } else {
        printf("Arac dosyasi bos.\n");
    }

    fclose(farac);
    fclose(fcopy);
    remove("arac_copy.txt");

    fkirala = fopen("kirala.txt", "r+");

    while(!feof(fkirala)){
        fscanf(fkirala, "%d | %d | %d.%d.%d | %d.%d.%d", &kiralama.plaka, &kiralama.musteri_no, &gun1, &ay1, &yil1, &gun2, &ay2, &yil2);  
        if (iade.plaka == kiralama.plaka) 
            break; 
        else
            continue;
    }


    if(ay1 == ay2){
        ucret = (gun2 - gun1) * fiyat;          
    } else {                                                                             
                                                                                    
        if(ay1 != 2 || ay1 != 4 || ay1 != 6 || ay1 != 9 || ay1 != 11){        
            if(ay1 == 2){                                                             
                if(yil1%4 == 0){                  
                    ucret += (29 - gun1);         
                }else {                             
                    ucret += (28 - gun1);
                }
            }else{
                ucret += (30 - gun1);
            }
        }else{
            ucret += (31 - gun1);
        }

        for (int i=(ay1 + 1);i<ay2;i++){
            if(ay1 != 2 || ay1 != 4 || ay1 != 6 || ay1 != 9 || ay1 != 11){
                if(ay1 == 2){
                    if(yil1%4 == 0){
                        ucret += 29;
                    }else {
                    ucret += 28;
                    }
                }else{
                    ucret += 30;
                }
            }else{
              ucret += 31 ;
            } 
        } 

        ucret += gun2;
        ucret *= fiyat;      
    }

    printf("Toplam ucret: %d \n\n", ucret);

    fclose(fkirala);
}

void main(){

    int islem = 0;

    while(islem == 0){
        printf("\n\n1. Arac Islemleri\n2. Musteri Islemleri\n3. Kiralama Islemleri\n4. Cikis\n\nYapmak istediginiz islemi giriniz: ");
        scanf("%d", &islem);

        switch (islem)
        {
        case 1:
            while(islem != 0){
                printf("\n\n1.Arac Ekle\n2.Arac Listele\n3.Arac Ara\n4.Arac Sil\n5.Cikis\nYapmak istediginiz islemi giriniz: ");
                scanf("%d", &islem);   

                switch (islem)
                {
                case 1:
                    arac_ekle();
                    break;

                case 2:
                    arac_listele();
                    break; 

                case 3:
                    arac_ara();
                    break; 

                case 4:
                    arac_sil();
                    break; 

                case 5:
                    islem = cikis(islem);
                    break;

                default:
                    printf("Yanlis tuslama yaptiniz\n\n");
                    islem = 1;
                    break;
                }
                
            }
            break;
        case 2:
            while (islem != 0){
                printf("\n\n1.Musteri Ekle\n2.Musteri Listele\n3.Musteri Ara\n4.Musteri Sil\n5.Cikis\nYapmak istediginiz islemi giriniz: ");
                scanf("%d", &islem);   

                switch (islem)
                {
                case 1:
                    musteri_ekle();
                    break;

                case 2:
                    musteri_listele();
                    break; 

                case 3:
                    musteri_ara();
                    break; 

                case 4:
                    musteri_sil();
                    break; 

                case 5:
                    islem = cikis(islem);
                    break;

                default:
                    printf("Yanlıs tuşlama yaptınız.\n\n");
                    islem = 1;
                    break;
                }
            }
            
            break;

        case 3:
            while(islem != 0){
                printf("\n\n1.Kirala\n2.Iade\n3.Cikis\nYapmak istediginiz islemi giriniz: ");
                scanf("%d", &islem);

                switch (islem)
                {
                case 1:
                    kirala();
                    break;

                case 2:
                    iade();
                    break;

                case 3:
                    islem = cikis(islem);
                    break;

                default:
                    printf("Yanlis tuslama yaptiniz\n\n");
                    islem = 1;
                    break;
                }
            }
            break;

        case 4:
            islem = cikis(islem);
            break;

        default:
            printf("Yanlis tuslama yaptiniz\n\n");
            islem = 0;
            break;
        }
    }
}
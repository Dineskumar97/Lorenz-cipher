//changed percentage =  51.7568%

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// wheel settings for the Lorenz cipher
char chi1[41] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1};
char chi2[31] = {1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0};
char chi3[29] = {1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0};
char chi4[26] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1};
char chi5[23] = {1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0};

char psi1[43] = {1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0};
char psi2[47] = {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0};
char psi3[51] = {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1};
char psi4[53] = {0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1};
char psi5[59] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0};

char mu1[61] = {0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0};
char mu2[37] = {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};

// wheel rotation (shift register operation)
void move_chi_pos(int chi_pos[5])
{
    chi_pos[0] = (chi_pos[0] + 1) % 41;
    chi_pos[1] = (chi_pos[1] + 1) % 31;
    chi_pos[2] = (chi_pos[2] + 1) % 29;
    chi_pos[3] = (chi_pos[3] + 1) % 26;
    chi_pos[4] = (chi_pos[4] + 1) % 23;
}

void move_psi_pos(int psi_pos[5])
{
    psi_pos[0] = (psi_pos[0] + 1) % 43;
    psi_pos[1] = (psi_pos[1] + 1) % 47;
    psi_pos[2] = (psi_pos[2] + 1) % 51;
    psi_pos[3] = (psi_pos[3] + 1) % 53;
    psi_pos[4] = (psi_pos[4] + 1) % 59;
}

void move_mu_pos1(int *mu_pos1)
{
    *mu_pos1 = (*mu_pos1 + 1) % 61;
}

void move_mu_pos2(int *mu_pos2)
{
    *mu_pos2 = (*mu_pos2 + 1) % 37;
}

// utility functions
void print_chi(int chi_pos[5])
{
    printf("%i ", chi1[chi_pos[0]]);
    printf("%i ", chi2[chi_pos[1]]);
    printf("%i ", chi3[chi_pos[2]]);
    printf("%i ", chi4[chi_pos[3]]);
    printf("%i ", chi5[chi_pos[4]]);
    printf("| ");
}

void print_psi(int psi_pos[5])
{
    printf("%i ", psi1[psi_pos[0]]);
    printf("%i ", psi2[psi_pos[1]]);
    printf("%i ", psi3[psi_pos[2]]);
    printf("%i ", psi4[psi_pos[3]]);
    printf("%i ", psi5[psi_pos[4]]);
    printf("| ");
}

void print_mu(int mu_pos[2])
{
    printf("%i ", mu1[mu_pos[0]]);
    printf("%i ", mu2[mu_pos[1]]);
    printf("| ");
}

void encrypt(int plain[5], int keyStrean[5])
{
}

//function to generate key stream
char *generateKeyStream(int chi_pos[5], int psi_pos[5], int mu_pos[2])
{
    static char K[5];

    char clock_mu_wheel;
    char clock_psi_wheel;

    // 1. Encrypting each 5-bit word at time t
    //    K_t = chi_t^i \xor psi_{t_chi}^i
    K[0] = chi1[chi_pos[0]] ^ psi1[psi_pos[0]];
    K[1] = chi2[chi_pos[1]] ^ psi2[psi_pos[1]];
    K[2] = chi3[chi_pos[2]] ^ psi3[psi_pos[2]];
    K[3] = chi4[chi_pos[3]] ^ psi4[psi_pos[3]];
    K[4] = chi5[chi_pos[4]] ^ psi5[psi_pos[4]];

    // print_chi(chi_pos);
    // print_psi(psi_pos);
    // print_mu(mu_pos);

    clock_mu_wheel = 0;
    clock_psi_wheel = 0;

    // 2. clock ticked as t = t+1
    //    move all chi wheels
    move_chi_pos(chi_pos);
    //    move first mu wheel
    move_mu_pos1(&mu_pos[0]);

    // 3. check for mu wheel rotation
    if (mu1[mu_pos[0]] == 1)
        clock_mu_wheel = 1;
    //    move mu wheels
    if (clock_mu_wheel == 1)
    {
        move_mu_pos2(&mu_pos[1]);
    }

    // 4. check for psi wheel rotation
    if (mu2[mu_pos[1]] == 1)
        clock_psi_wheel = 1;
    //    move psi wheels
    if (clock_psi_wheel == 1)
        move_psi_pos(psi_pos);

    // 5. output K_t
    for (int i = 0; i < 5; i++)
    {
        //printf("%i ",K[i]);
    }

    return K;
}

void main()
{
    FILE *fp = fopen("wiki.txt", "r");
    FILE *enc = fopen("cipherText.txt", "w");
    FILE *keyStr = fopen("keyStream.txt", "w");


    char str[50];
    char buff[5];

    float totalBits = 0, changedBits = 0;

    // Starting positions of wheels
    int chi_pos[5] = {0, 0, 0, 0, 0};
    int psi_pos[5] = {0, 0, 0, 0, 0};
    int mu_pos[2] = {0, 0};

    char encText[5];
    char *k1;

    //read input file fifty characters by fifty characters from file plain.txt
    while (fgets(str, 50, fp) != NULL)
    {
        //get a letter by letter from each word and encryptng each letter
        for (int i = 0; i < strlen(str); i++)
        {
            char letter = str[i];
            printf("%c: ", letter);
            if (str[i] == 'a' || str[i] == 'A' || str[i] == '-')
            {
                strcpy(buff, "00011");
            }
            else if (str[i] == 'b' || str[i] == 'B' || str[i] == '?')
            {
                strcpy(buff, "11001");
            }
            else if (str[i] == 'c' || str[i] == 'C' || str[i] == ':')
            {
                strcpy(buff, "01110");
            }
            else if (str[i] == 'd' || str[i] == 'D')
            {
                strcpy(buff, "01001");
            }
            else if (str[i] == 'e' || str[i] == 'E' || str[i] == '3')
            {
                strcpy(buff, "00001");
            }
            else if (str[i] == 'f' || str[i] == 'F' || str[i] == '!')
            {
                strcpy(buff, "01101");
            }
            else if (str[i] == 'g' || str[i] == 'G' || str[i] == '&')
            {
                strcpy(buff, "11010");
            }
            else if (str[i] == 'h' || str[i] == 'H')
            {
                strcpy(buff, "10100");
            }
            else if (str[i] == 'i' || str[i] == 'I' || str[i] == '8')
            {
                strcpy(buff, "00110");
            }
            else if (str[i] == 'j' || str[i] == 'J')
            {
                strcpy(buff, "01011");
            }
            else if (str[i] == 'k' || str[i] == 'K' || str[i] == '(')
            {
                strcpy(buff, "01111");
            }
            else if (str[i] == 'l' || str[i] == 'L' || str[i] == ')')
            {
                strcpy(buff, "10010");
            }
            else if (str[i] == 'm' || str[i] == 'M' || str[i] == '.')
            {
                strcpy(buff, "11100");
            }
            else if (str[i] == 'n' || str[i] == 'N' || str[i] == ',')
            {
                strcpy(buff, "01100");
            }
            else if (str[i] == 'o' || str[i] == 'O' || str[i] == '9')
            {
                strcpy(buff, "11000");
            }
            else if (str[i] == 'p' || str[i] == 'P' || str[i] == '0')
            {
                strcpy(buff, "10110");
            }
            else if (str[i] == 'q' || str[i] == 'Q' || str[i] == '1')
            {
                strcpy(buff, "10111");
            }
            else if (str[i] == 'r' || str[i] == 'R' || str[i] == '4')
            {
                strcpy(buff, "01010");
            }
            else if (str[i] == 's' || str[i] == 'S' || str[i] == '\'')
            {
                strcpy(buff, "00101");
            }
            else if (str[i] == 't' || str[i] == 'T' || str[i] == '5')
            {
                strcpy(buff, "10000");
            }
            else if (str[i] == 'u' || str[i] == 'U' || str[i] == '7')
            {
                strcpy(buff, "00111");
            }
            else if (str[i] == 'v' || str[i] == 'V' || str[i] == '=')
            {
                strcpy(buff, "11110");
            }
            else if (str[i] == 'w' || str[i] == 'W' || str[i] == '2')
            {
                strcpy(buff, "10011");
            }
            else if (str[i] == 'x' || str[i] == 'X' || str[i] == '/')
            {
                strcpy(buff, "11101");
            }
            else if (str[i] == 'y' || str[i] == 'Y' || str[i] == '6')
            {
                strcpy(buff, "10101");
            }
            else if (str[i] == 'z' || str[i] == 'Z' || str[i] == '+')
            {
                strcpy(buff, "10001");
            }
            else if (str[i] == ' ')
            {
                strcpy(buff, "00100");
            }
            else if (str[i] == '\n')
            {
                strcpy(buff, "00010");
            }
            else
            {
                strcpy(buff, "00000");
            }

            //printing the read letter to concole
            for (int p = 0; p < 5; p++)
            {
                printf("%c", buff[p]);
            }
            printf(" | ");

            //get the generated key stream
            k1 = generateKeyStream(chi_pos, psi_pos, mu_pos);

            //writing the generated key stream to keyStream.txt file and printing to concole
            printf("Key Stream: ");
            for (int p = 0; p < 5; p++)
            {
                fprintf(keyStr, "%i", k1[p]);
                printf("%i", k1[p]);
            }
            printf(" | ");
            fprintf(keyStr, " ");

            //encrypting the letter
            encText[0] = k1[0] ^ (int)(buff[0] - '0');
            encText[1] = k1[1] ^ (int)(buff[1] - '0');
            encText[2] = k1[2] ^ (int)(buff[2] - '0');
            encText[3] = k1[3] ^ (int)(buff[3] - '0');
            encText[4] = k1[4] ^ (int)(buff[4] - '0');

            //writing the encrypted text to cipherText.txt file and printing to console
            //calculating the total number of bits and changed number of bits
            printf("Encrypted Character: ");
            for (int p = 0; p < 5; p++)
            {
                fprintf(enc, "%i", encText[p]);
                printf("%i", encText[p]);

                if (encText[p] != (int)(buff[0] - '0'))
                {
                    totalBits += 1;
                    changedBits += 1;
                }
                else
                {
                    totalBits += 1;
                }
            }
            fprintf(enc, " ");
            printf("\n");
        }
    }

    //calculating the percentage of changed bits and printing to console
    float changedPercentage = (changedBits / totalBits) * 100;
    printf("Total bits: %g\n", totalBits);
    printf("Changed bits: %g\n", changedBits);
    printf("Changed percentage: %g", changedPercentage);

    fclose(fp);
    fclose(enc);
    fclose(keyStr);
}

//plain text
/*Sri Lanka officially the Democratic Socialist Republic of Sri Lanka, is an island country in South Asia, located in the Indian Ocean to the southwest of the Bay of Bengal and to the southeast of the Arabian Sea. The island is historically and culturally intertwined with the Indian subcontinent, but is geographically separated from the Indian subcontinent by the Gulf of Mannar and the Palk Strait. The legislative capital, Sri Jayawardenepura Kotte, is a suburb of the commercial capital and largest city, Colombo.
Sri Lanka's documented history spans 3,000 years, with evidence of pre-historic human settlements dating back to at least 125,000 years. It has a rich cultural heritage and the first known Buddhist writings of Sri Lanka, the Pali Canon, date back to the Fourth Buddhist council in 29 BC. Its geographic location and deep harbours made it of great strategic importance from the time of the ancient Silk Road through to the modern Maritime Silk Road.
Sri Lanka was known from the beginning of British colonial rule as Ceylon .A nationalist political movement arose in the country in the early 20th century to obtain political independence, which was granted in 1948; the country became a republic and adopted its current name in 1972. Sri Lanka's recent history has been marred by a 30 year civil war, which decisively ended when the Sri Lanka Armed Forces defeated the Liberation Tigers of Tamil Eelam (LTTE) in 2009.
The current constitution stipulates the political system as a republic and a unitary state governed by a semi presidential system. It has had a long history of international engagement, as a founding member of the South Asian Association for Regional Cooperation (SAARC), and a member of the United Nations, the Commonwealth of Nations, the G77, and the Non-Aligned Movement. Along with the Maldives, Sri Lanka is one of only two South Asian countries rated "high" on the Human Development Index (HDI), with its HDI rating and per capita income the highest among South Asian nations.[10] The Sri Lankan constitution accords Buddhism the "foremost place", although it does not identify it as a state religion. Buddhism is given special privileges in the Sri Lankan constitution.
The island is home to many cultures, languages and ethnicities. The majority of the population is from the Sinhalese ethnicity, while a large minority of Tamils have also played an influential role in the island's history. Moors, Burghers, Malays, Chinese, and the indigenous Vedda are also established groups on the island.
 In antiquity, Sri Lanka was known to travellers by a variety of names. According to the Mahavamsa, the legendary Prince Vijaya named the land Tambapanni ("copper-red hands" or "copper-red earth"), because his followers' hands were reddened by the red soil of the area. In Hindu mythology, such as the Ramayana, the island was referred to as Lanka ("Island"). The Tamil term Eelam was used to designate the whole island in Sangam literature.
Ancient Greek geographers called it Taprobana from the word Tambapanni. The Persians and Arabs referred to it as Sarandib (the origin of the word "serendipity") from Cerentivu or Siṃhaladvipaḥ. Ceilao, the name given to Sri Lanka by the Portuguese Empire when it arrived in 1505, was transliterated into English as Ceylon. As a British crown colony, the island was known as Ceylon; it achieved independence as the Dominion of Ceylon in 1948.
The country is now known in Sinhalese as Śri Lanka and in Tamil as Ilaṅkai. In 1972, its formal name was changed to "Free, Sovereign and Independent Republic of Sri Lanka". Later in 1978 it was changed to the "Democratic Socialist Republic of Sri Lanka". As the name Ceylon still appears in the names of a number of organisations, the Sri Lankan government announced in 2011 a plan to rename all those over which it has authority.
The pre-history of Sri Lanka goes back 125,000 years and possibly even as far back as 500,000 years. The era spans the Palaeolithic, Mesolithic and early Iron Ages. Among the Paleolithic human settlements discovered in Sri Lanka, Pahiyangala (named after the Chinese traveller monk Faxian), which dates back to 37,000 BP,[35] Batadombalena (28,500 BP)[36] and Belilena (12,000 BP) are the most important. In these caves, archaeologists have found the remains of anatomically modern humans which they have named Balangoda Man, and other evidence[37] suggesting that they may have engaged in agriculture and kept domestic dogs for driving game.[38]
One of the first written references to the island is found in the Indian epic Ramayana, which provides details of a kingdom named Lanka that was created by the divine sculptor Vishwakarma for Kubera, the Lord of Wealth.[39] It is said that Kubera was overthrown by his demon stepbrother Ravana, the powerful emperor who built a mythical flying machine named Dandu Monara.[40] The modern city of Wariyapola is described as Ravana's airport.[41]
Early inhabitants of Sri Lanka were probably ancestors of the Vedda people,[42] an indigenous people numbering approximately 2,500 living in modern-day Sri Lanka. The 19th-century Irish historian James Emerson Tennent theorized that Galle, a city in southern Sri Lanka, was the ancient seaport of Tarshish from which King Solomon is said to have drawn ivory, peacocks, and other valuables.
According to the Mahavamsa, a chronicle written in Paḷi, the original inhabitants of Sri Lanka are the Yakshas and Nagas. Ancient cemeteries that were used before 600 BC and other signs of advanced civilization have also been discovered in Sri Lanka.[43] Sinhalese history traditionally starts in 543 BC with the arrival of Prince Vijaya, a semi-legendary prince who sailed with 700 followers to Sri Lanka, after being expelled from Vanga Kingdom (present-day Bengal).[44] He established the Kingdom of Tambapanni, near modern-day Mannar. Vijaya (Singha) is the first of the approximately 189 native monarchs of Sri Lanka described in chronicles such as the Dipavamsa, Mahavaṃsa, Cūḷavaṃsa, and Rajavaliya (see list of Sinhalese monarchs). Sri Lankan dynastic history ended in 1815, when the island became part of the British Empire.[45]
The Anuradhapura Kingdom was established in 380 BC during the reign of Pandukabhaya of Anuradhapura. Thereafter, Anuradhapura served as the capital city of the country for nearly 1,400 years.[46] Ancient Sri Lankans excelled at building certain types of structures (constructions) such as tanks, dagobas and palaces.[47] Society underwent a major transformation during the reign of Devanampiya Tissa of Anuradhapura, with the arrival of Buddhism from India. In 250 BC,[48] Mahinda, the son of the Mauryan Emperor Ashoka and a bhikkhu (Buddhist monk) arrived in Mihintale carrying the message of Buddhism.[49] His mission won over the monarch, who embraced the faith and propagated it throughout the Sinhalese population.[50]

*/

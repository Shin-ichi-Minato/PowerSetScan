# PowerSetScan

A program for detecting a hotspot cluster from a statistical data which is partitioned by geographical regions such as prefectures or cities. This program enumerates all combinatorial regions which are more significant than a given threshold value based on spatial scan statistic.

# Requirement

g++ (GCC) 7.3.0 or later

# Installation

"make" produces an executable program "pss".

# Usage

__pss \<filename\> \<min_scanstat\> [\<flag\> [\<number\>] ]*__  
  
\<flag\>:  
**-p**             : print all hotspots  
**-hm**            : print hotspot-heatmap  
**-ber**           : using Bernoulli-model statistic  
**-chi**           : using Chi-squared statistic  
**-nmax \<number\>**   : bounded search with n(Z) <= nmax  
**-cmin \<number\>**   : bounded search with c(Z) >= cmin  
**-r \<number\>**      : repeat execution by uniformly randomized data  
  
(Just execute "pss" to see this help.)

# Demo

**> pss H28J.dat 100**  
**** PowerSetScan (v.1.80) ****  
[HotSpotHits,  MaxStats]  
696559, 116.341358  
  
  
**> pss H28J.dat 116**  
**** PowerSetScan (v.1.80) ****  
[HotSpotHits,  MaxStats]  
5,      116.341358  
  
  
**> pss H28J.dat 116 -p**  
**** PowerSetScan (v.1.80) ****  
116.341358 (n:37001198 c:7365 c/n:0.000199)  
 5-Akita 3-Iwate 30-Wakayama 15-Niigata 19-Yamanashi 2-Aomori 10-Gunma 6-Yamagata 39-Kochi 45-Miyazaki 7-Fukushima 9-Tochigi 32-Shimane 16-Toyama 4-Miyagi 38-Ehime 1-Hokkaido 43-Kumamoto 18-Fukui 20-Nagano 36-Tokushima 22-Shizuoka  
\----  
116.297555 (n:38421061 c:7618 c/n:0.000198)  
 5-Akita 3-Iwate 30-Wakayama 15-Niigata 19-Yamanashi 2-Aomori 10-Gunma 6-Yamagata 39-Kochi 45-Miyazaki 7-Fukushima 9-Tochigi 32-Shimane 16-Toyama 4-Miyagi 38-Ehime 1-Hokkaido 43-Kumamoto 18-Fukui 20-Nagano 36-Tokushima 22-Shizuoka 25-Shiga  
\----  
116.309051 (n:40497256 c:7987 c/n:0.000197)  
 5-Akita 3-Iwate 30-Wakayama 15-Niigata 19-Yamanashi 2-Aomori 10-Gunma 6-Yamagata 39-Kochi 45-Miyazaki 7-Fukushima 9-Tochigi 32-Shimane 16-Toyama 4-Miyagi 38-Ehime 1-Hokkaido 43-Kumamoto 18-Fukui 20-Nagano 36-Tokushima 22-Shizuoka 25-Shiga 21-Gifu  
\----  
116.142132 (n:41958487 c:8245 c/n:0.000197)  
 5-Akita 3-Iwate 30-Wakayama 15-Niigata 19-Yamanashi 2-Aomori 10-Gunma 6-Yamagata 39-Kochi 45-Miyazaki 7-Fukushima 9-Tochigi 32-Shimane 16-Toyama 4-Miyagi 38-Ehime 1-Hokkaido 43-Kumamoto 18-Fukui 20-Nagano 36-Tokushima 22-Shizuoka 25-Shiga 21-Gifu 47-Okinawa  
\----  
116.124037 (n:39077393 c:7734 c/n:0.000198)  
 5-Akita 3-Iwate 30-Wakayama 15-Niigata 19-Yamanashi 2-Aomori 10-Gunma 6-Yamagata 39-Kochi 45-Miyazaki 7-Fukushima 9-Tochigi 32-Shimane 16-Toyama 4-Miyagi 38-Ehime 1-Hokkaido 43-Kumamoto 18-Fukui 20-Nagano 36-Tokushima 22-Shizuoka 21-Gifu  
\----  
[HotSpotHits,  MaxStats]  
5,      116.341358  


# Author

Shin-ichi MINATO  
at Graduate School of Informatics, Kyoto University.  
(https://www.lab2.kuis.kyoto-u.ac.jp/minato/)

# License

PowerSetScan is under MIT license (https://en.wikipedia.org/wiki/MIT_License)

# Files

**PSS_Table.h** : Header file.  
**PSS_Table.cc** : Source file.  
**PSS_Main.cc** : Source file.  
**Makefile** : Makefile for make.  
**test.dat** : very small test data.  
**sids.dat** : North Carolina SIDS data.  
**sids200.dat** : Dupplicated data of sids.dat with 200 counties.  
**sids300.dat** : Dupplicated data of sids.dat with 300 counties.  
**sids400.dat** : Dupplicated data of sids.dat with 400 counties.  
**H28J.dat** : "H28 Jisatsu" data of 47 prefectures in Japan.  
**H28J94.dat** : Dupplicated data of H28J.dat with 94 prefectures.  
**SDM2019-Minato.pdf** : Conference paper shown in SDM 2019.  
**IPSJ-AL201809-Minato.pdf** : Paper shown in IPSJ-AL201809. (in Japanese)  




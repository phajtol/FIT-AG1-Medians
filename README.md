# FIT-AG1-Medians

This is a project created as a homework for subject Algorithms and Graphs 1 (BI-AG1 - Algoritmy a grafy 1) at FIT CTU.

Full assignment in Czech language is below.

Summary of the assignment: Create a data structure that will allow adding and removing numbers and will be able to quickly return median from added data.

---
The data structure I have decided to implement is AVL tree.

My solution is in file `solution.cpp`, text files contain test data for basic scenarios with reference solutions.

My solution has received maximum points (including big data #2 test).

# Assignment

Ve velmi vzdálené zemi již několik týdnů panuje vzrušená atmosféra. Blíží se totiž volby a celý národ tak s napětím očekává, že opět po několika letech může přijít změna k lepšímu. Na nohou však nejsou pouze občané, ale také politici, kteří v nejbližších dnech v předvolebních debatách svedou tvrdé souboje o politické body. Zejména těžkou pozici mají členové vlády, kteří by velmi rádi obhájili svůj mandát. U těch se totiž volební přízeň odvíjí zejména od úspěchů či neúspěchů v předešlém funkčním období.

Asi nejtěžší situaci má stávající ministr financí. Není totiž žádným tajemstvím, že jeho působení ve vládě by se dalo shrnout v nejlepším jako tristní. Konkrétně za jeho působení takřka všem klesly příjmy, což spoustu lidí posunulo pod hranici životního minima. S takovými výsledky by v předvolebních debatách ministr jistě neokouzlil, a tak se svými poradci vymyslel záchranný plán. Kdyby přeci mohl v debatách ukazovat nějakou hodnotu, která není vylhaná, vychází z reálných příjmů, nevypadá na první pohled tak zle, ale u které zároveň lidé nerozumí způsobu jejího výpočtu, to by byla výhra! Jako první padla volba na aritmetický průměr, ale průzkum ukázal, že lidé této hodnotě rozumí. Z toho důvodu byl zvolen medián, který se v obecném povědomí vyskytuje výrazně méně. Konkrétně by tak ministr pro úspěch v debatách potřeboval následující - kdykoliv se moderátor či politický oponent zeptají na příjmy v daném finančním rozpětí, ministr odpoví mediánem příjmů všech lidí, kteří v daném rozpětí mají příjem. Situace je však ztížená tím, že příjmy lidí se neustále mění. To znamená, že ze seznamu příjmů všech lidí mohou být některé příjmy odstraněny, a naopak některé příjmy mohou do seznamu přibýt (změna příjmu se dá představit jako kombinace odstranění staré a přibytí nové hodnoty). Je tedy nutné, aby ministr měl rychle k dispozici mediány pro daná rozpětí příjmů v rámci dynamicky se měnícího seznamu příjmů.

Jelikož se jedná o velmi riskantní předvolební pokus, musel být pro efektivní a správné řešení úlohy vybrán ostřílený programátor, který se nebojí zhostit se úkolu takovéto podstaty. Volba padla na vás. Pro zadanou posloupnost přibývání/odstraňování příjmů a rozsahů pro hledání mediánu, musíte vytvořit program, který splní požadavky uvedené výše. Vzhledem k absolutnímu utajení nelze při řešení této úlohy používat takřka žádný cizí kód. Toto opatření se týká i knihovny STL, kterou tak použít nemůžete.

#### Formát vstupu a výstupu:

- Vstup sestává z určitého počtu řádek na vstupu, kde každá kóduje jeden příkaz, viz níže uvedené příkazy v uvozovkách:
  - **`1 X`**
kde `X` je přirozené číslo, `1 ≤ X ≤ 10^9`, znamená přidej do seznamu příjmů příjem o hodnotě `X`.
  - **`2 X`**
kde `X` je přirozené číslo, `1 ≤ X ≤ 10^9`, znamená odeber ze seznamu příjmů příjem o hodnotě `X`.
  - **`3 X Y`**
kde `X`, `Y` jsou přirozená čísla, `1 ≤ X`, `Y ≤ 10^9`, `X ≤ Y`, znamená nalezni medián (viz definice níže) čísel v rozsahu od `X` do `Y` (včetně) ze stávajícího seznamu příjmů a vypiš jej na samostatný řádek.
  - **`4`**
znamená, že již začaly volby a že žádný další příkaz již následovat nebude; tento příkaz je zaručeně jako poslední na vstupu.
- Můžete se spolehnout, že vstup je zadán korektně.

Dále:

- Medián čísel v rozsahu od `X` do `Y` ze stávajícího seznamu příjmu definujeme takto: je-li ve stávajícím seznamu příjmů k příjmů s hodnotou v rozsahu mezi `X` a `Y` (včetně), je medián `⌈k⁄2⌉`-tý nejmenší z těchto příjmů.
- Nenachází-li se pro daný rozsah v seznamu příjmů žádný příjem, vypište na výstup řádek s řetězcem "notfound" (bez uvozovek).
- Může se stát, že vzhledem k úřednické chybě dostane váš program požadavek na smazání takového příjmu, který se v seznamu příjmů nevyskytuje. V takovém případě požadavek ignorujte.
- Naopak se nikdy nestane, že by se v seznamu najednou vyskytovalo (po příslušných požadavcích na přidání) více příjmů o stejné hodnotě. Pokud však bude příjem o určité hodnotě ze seznamu v nějaký moment odebrán, může být později do seznamu znovu přidán.

#### Bodové podmínky:

- Pro splnění povinných testů je zapotřebí, aby program fungoval korektně pro vstupy o nejvýše 1 000 příkazech. Příkazy budou pouze typu 1, 3 a 4.
- Pro splnění testu velkými daty #1 musí program splnit časový limit pro vstupy o nejvýše 1 000 000 příkazech. Příkazy budou pouze typu 1, 3 a 4.
- Pro splnění testu velkými daty #2 musí program splnit časový limit pro vstupy o nejvýše 1 000 000 příkazech. Příkazy mohou být všech typů.
- Testy podle ukázky jsou z důvodu omezení typů příkazů na vstupu provedeny ve dvou různých testech. První z nich testuje ukázkové vstupy 1 a 2 a je povinný. Druhý testuje ukázkový vstup 3 a je nepovinný.

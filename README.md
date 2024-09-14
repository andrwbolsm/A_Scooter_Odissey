# A_Scooter_Odissey
Jogo em C desenvolvido para a disciplina de Algoritmos e Programação no Curso de Engenharia Aeroespacial da Universidade Federal de Santa Maria, UFSM.

O “A Scooter Odyssey” foi inspirado no jogo T-Rex Game, mais conhecido como “jogo 
do dinossauro” que é integrado ao navegador do Google Chrome. Similar ao jogo do 
dinossauro, A Scooter Odyssey conta com o objetivo de pular obstáculos que surgem 
aleatoriamente diante do jogador, juntamente com a presença de um score que o desafia atingir 
a maior pontuação. 
O diferencial do jogo está justamente em ambientar a jogatina no campus da 
Universidade Federal de Santa Maria, com menções ao Centro de Tecnologia, a cafeteria 
Cosmopolita, o Planetário, entre outros. Diferentemente do jogo do dinossauro, aqui os 
obstáculos são o vírus da COVID-19, e controlamos um personagem que utiliza um patinete 
para locomover-se, enquanto a velocidade do jogo aumenta à medida que ele salta. Há também 
um adicional de sobrevidas, representado por cafés que o jogador pode coletar, sendo possível 
acumular no máximo três. 
À medida que o café é acumulado, consta-se a quantidade de cafés ingeridos no canto 
superior esquerdo da tela e o visual do protagonista muda. Quando ele choca-se com o vírus, 
perde-se um café. Caso não tenha nenhum, este muda seu visual para um personagem menor e 
doente e se colidir mais uma vez, é fim de jogo, sendo necessário apertar enter para zerar o 
score e reiniciar a jogatina. O score consta-se no canto superior direito, logo após a pontuação 
“HS” que é a maior pontuação do jogador desde que este iniciou o jogo. 
Tratando mais especificamente do código, utilizou-se como base os conhecimentos 
adquiridos na disciplina de Algoritmos e Programação e funções da biblioteca Allegro, 
retiradas do site oficial dos desenvolvedores. A lógica do jogo é basicamente os bitmaps do 
fundo e dos obstáculos transitando a uma determinada velocidade para a esquerda, passando a 
impressão de movimento, enquanto o bitmap do protagonista mantém-se fixo no eixo x, 
movimentando-se para cima sempre que o jogador aperta a tecla up, simulando o pulo.
Para programar o pulo, assim que o jogador aperta a tecla up, a variável booleana 
“jump” torna-se verdadeira, somando-se determinada quantidade na variável que representa 
sua posição no eixo y, e assim que ele atinge determinada altura na tela, a variável jump tornase falsa, diminuindo-se o dobro de quantidade da posição, até parar na sua posição inicial, 
simulando assim a gravidade. Mais informações acerca do código constam-se no próprio corpo 
dele, na forma de comentários.
Os desenvolvedores esperam que o jogo possa agradar e divertir aqueles que o jogam, 
e que se torne um passatempo desafiador e também nostálgico pelos diversos elementos que 
relembram os velhos jogos 2D, como o cenário e sons 8 bits.

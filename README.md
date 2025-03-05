# 🏛️ Philosophers

<p align="center">
  <img src="https://github.com/mbah24-dev/mbah24-dev/blob/main/42_badges/philosopherse.png" alt="philosophers 42 project badge"/>
</p>

Le projet 42 Philosophers est une implémentation du célèbre problème des philosophes en C. Il met en jeu la gestion des threads, des mutex et des sémaphores pour assurer une synchronisation correcte et éviter les deadlocks.

<h2>🏛️ Le Problème</h2>
<p>Cinq philosophes sont assis autour d'une table et passent leur temps à <strong>penser</strong> ou <strong>manger</strong>. Pour manger, ils doivent prendre deux fourchettes (une à gauche et une à droite). Chaque fourchette ne peut être utilisée que par un philosophe à la fois, ce qui pose des problèmes de synchronisation.</p>

<h2>🔧 Fonctionnalités</h2>
<ul>
    <li>✅ Gestion efficace des threads (pthread)</li>
    <li>✅ Synchronisation avec mutex et sémaphores</li>
    <li>✅ Prévention du deadlock et famine</li>
    <li>✅ Simulation fluide et réaliste</li>
</ul>

<h2>🚀 Installation</h2>
<pre><code># Cloner le repo

<h2>🎮 Utilisation</h2>
<pre><code>./philo &lt;nombre_de_philosophes&gt; &lt;temps_pour_mourir&gt; &lt;temps_pour_manger&gt; &lt;temps_pour_penser&gt; [nombre_de_repas]</code></pre>
<p>Exemple :</p>
<pre><code>./philo 5 800 200 200</code></pre>
<p>Cela lance une simulation avec <strong>5 philosophes</strong>, un <strong>temps de vie</strong> de <strong>800ms</strong>, un <strong>temps pour manger</strong> de <strong>200ms</strong>, et un <strong>temps pour penser</strong> de <strong>200ms</strong>.</p>

<h2>📜 Règles</h2>
<ul>
    <li>Un philosophe meurt s'il ne mange pas à temps.</li>
    <li>Les fourchettes sont partagées et doivent être prises dans le bon ordre.</li>
    <li>Pas de deadlocks autorisés.</li>
    <li>Une simulation correcte doit respecter ces contraintes sans comportements inattendus.</li>
</ul>

<h2>🛠️ Technologies</h2>
<ul>
    <li><strong>C (pthread, mutex, sémaphores)</strong></li>
    <li><strong>Makefile</strong> pour la compilation</li>
</ul>

<h2>📖 Ressources utiles</h2>
<ul>
    <li><a href="https://man7.org/linux/man-pages/man7/pthreads.7.html">Pthread documentation</a></li>
    <li><a href="https://www.geeksforgeeks.org/mutex-and-semaphores-in-c/">Mutex et sémaphores en C</a></li>
</ul>

<h2>📢 Contribuer</h2>
<p>Les contributions sont les bienvenues ! Pour toute amélioration, ouvrez une <strong>issue</strong> ou soumettez une <strong>pull request</strong>.</p>

<h2>📜 Licence</h2>
<p>Ce projet est sous licence <strong>MIT</strong>. Vous êtes libre de l'utiliser et de le modifier.</p>

<hr>
<p>🧠 <em>"Manger pour penser, penser pour manger."</em> 🍽️</p>

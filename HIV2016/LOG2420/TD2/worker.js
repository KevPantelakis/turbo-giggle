
self.importScripts("CompteurJetons.js");
var compteur = new CompteurJetons();

self.addEventListener('message', function(e) {
    var gen = compteur.compterJetons(e.data);

    var progress = 0;

while (progress != 100){
    progress = gen.next().value;
    var a = [compteur.getJetons(), progress];
    postMessage(a);

}
  
}, false);
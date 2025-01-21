# BitLife Game
BitLife ist eine realistische und humorvolle Lebenssimulation, die es dir ermöglicht, ein virtuelles Leben zu führen und Entscheidungen zu treffen, die den Verlauf deines Charakters beeinflussen. Vom ersten Atemzug bis zum Tod erlebst du alle wichtigen Etappen des Lebens und kannst dabei selbst entscheiden, wie dein Charakter sein Leben gestaltet.

## Funktionen

### Shop
Der C++-Code implementiert ein Shop-System für ein BitLife-Spiel, bei dem der Spieler Items kaufen und verkaufen kann:
- openShop: Zeigt die verfügbaren Items an, ermöglicht dem Spieler den Kauf eines Items und prüft, ob er genug Geld hat. Wenn der Spieler das Item schon besitzt, wird die Menge aktualisiert.
- sellItem: Ermöglicht dem Spieler, Gegenstände aus seinem Inventar zu verkaufen und das Guthaben zu erhöhen.
- checkForItem: Prüft, ob ein Item im Inventar des Spielers vorhanden ist.
- generateShop: Erzeugt zufällig einen Shop mit verschiedenen Items (Getränke, Snacks, Autos), abhängig vom Shop-Typ (z. B. Convenience Store oder Autohaus).

Das System ermöglicht es dem Spieler, Items zu kaufen und zu verkaufen und mit verschiedenen Shops im Spiel zu interagieren.

### Job
Der C++-Code ermöglicht es dem Spieler, zufällig einen Job zu wählen oder zu wechseln.
- getJobVector: Erstellt eine Liste von Jobs mit zufälligen Gehältern und Erfahrungswerten.
- getRandomJob: Wählt zufällig einen Job aus der Liste basierend auf Gewichtung.
- changeJob: Bietet dem Spieler posOptions Jobangebote, aus denen er einen auswählen kann.

Das System erlaubt es dem Spieler, zwischen verschiedenen Berufen zu wählen und die Karriere im Spiel anzupassen.

### Events
Der C++-Code implementiert verschiedene zufällige Ereignisse, die während des Spiels auftreten können. Hier sind die wichtigsten Funktionen zusammengefasst:
- randomEventSelector: Wählt zufällig ein Ereignis aus, das an einem bestimmten Tag im Spiel auftreten kann. Die Wahrscheinlichkeit hängt von Faktoren wie der kriminellen Reputation des Spielers ab.
- dating: Der Spieler kann jemanden um ein Date bitten oder selbst gefragt werden. Je nach Entscheidung kann er einen Partner gewinnen oder abgelehnt werden, was seine mentale Gesundheit beeinträchtigen kann.
- prank: Der Spieler kann einen Streich spielen, der entweder erfolgreich ist oder negative Konsequenzen wie eine Gehaltskürzung oder Entlassung nach sich zieht.
- policeInvestigation: Der Spieler wird von der Polizei zu einer Straftat befragt. Je nachdem, ob er die Wahrheit sagt oder nicht, kann seine kriminelle Reputation steigen oder er wird von "Homies" bestraft.
- winRandomGiveaway: Der Spieler kann bei einem zufälligen Gewinnspiel gewinnen, was entweder Geld oder ein Item wie ein Telefon, VR-Headset oder Sportwagen sein kann.
- naturalDisaster: Bei einer Naturkatastrophe kann das Haus des Spielers beschädigt werden, wenn er kein starkes Haus besitzt.
- makeDonation: Der Spieler kann spenden oder seine Mental Health durch Weigerung, zu spenden, verlieren.
- becomeAdmin: Der Spieler kann befördert werden und erhält eine Gehaltserhöhung.
- slipOnBananaPeal: Der Spieler kann auf einer Bananenschale ausrutschen und Gesundheitsschaden erleiden.
- askedToCommitCrime: Der Spieler wird gefragt, ob er ein Verbrechen begehen möchte, was seine kriminelle Reputation beeinflussen kann.
- explosiveDiarrheaInPublicSpace: Der Spieler erleidet eine peinliche Panne in der Öffentlichkeit und muss eine Geldstrafe bezahlen.
- organisedCrime: Diese Funktion ist noch nicht definiert, aber könnte sich auf organisierte Kriminalität beziehen.

Diese Ereignisse bringen verschiedene Auswirkungen auf den Spieler, wie z. B. die Veränderung der Mental Health, des Geldes oder der kriminellen Reputation.
### Criminal Activity

### Name Generator

### Time Management

### Save Funktion

### Load Funktion

## UI

# Character:
* Character Component -> alles was wir vergessen haben. Respawn von player
* Character Movement -> Steering Behaviours (Move to point, Dash in direction) Aim and Shoot
* AI Controller -> Decision making for AI (DAUERT LANGE). Wann dashen (wohin) Prio für actions (Eventuell 3 States für AI (Flag,ball,none))
* Player Controller -> Liest in update input aus und ruft Character Movement methoden auf. 
* AABB Collider
* Rigidbody
* SpriteRenderer

# Ball:
* Rigidbody
* AABB Collider (Trigger)
* Ball Component -> hört auf collision events (Wenn mit spieler collidet dann check ob verbündeter oder feind. Wenn Feind: Damage, ball zerstört;
Wenn verbündeter: Pass( wenn kein Ball oder Flagge in hand)) pass counter wird um eins erhöht wenn noch nicht am maximum
Wenn Environemnt: prallt ab, (kleiner impuls von bande weg und landet auf boden) Wenn auf boden gelandet, beide Teams können aufheben. Behält stärke.
Variable die das Besitzerteam trackt
Wenn ball in hand trigger ausschalten
Reset to new position (called from respwaning mechanic)
Player had reference to ball gameobject if nullptr cant shoot
* SpriteRender

# Flag:
* Rigidbody
* AABB Collider (Trigger)
* Flag Component -> hört auf collision events (Aufheben wenn drüberrennen)
Variable die das Besitzerteam trackt
Wenn flag in hand trigger ausschalten
Reset to new position (called from respwaning mechanic)
Set player flag GO to flag GO  when picked up and to nullptr when dropped
baseID
* SpriteRender

# Base:
* Rigidbody
* AABB Collider (Trigger)
* Base Component -> hört auf collision events (Wenn player collidet und flagge hat und flagge richtige id hat, dann punkt und flagge resetten to new position)
Methode die entscheidet wo Flagge hingesetzt wird
* SpriteRender

# Wall:
* Rigidbody
* AABB Collider
* SpriteRender

# Score:
* Score Compoennt (int that tracks score and updates ui)

# IngameUI:
* Image for flag 
* Text for score

# Main Menu:
* Start (Wenn geklickt dann settingsmenü)
* Exit

# Settings:
* Spieleranzahl
* Bots werden geladen
___
___
___

# Nice to Have:

* Pause Menu
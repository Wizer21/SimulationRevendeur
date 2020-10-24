#include "Ville.h"

Ville::Ville(QString addNom, double addMultiplicateurGain, double addMultiplicateurFrais)
{
  nom = addNom;
  multiplicateurGain = addMultiplicateurGain;
  multiplicateurFrais = addMultiplicateurFrais;
}

QString Ville::getNom()
{
  return nom;
}

double Ville::getMultiplicateurGain()
{
  return multiplicateurGain;
}

double Ville::getFraisMultiplicateur()
{
  return multiplicateurFrais;
}

void Ville::setMultiplicateurGain(double value)
{
  multiplicateurGain = value;
}

void Ville::setFraisMultiplicateur(double value)
{
  multiplicateurFrais = value;
}

QString Ville::randomEvent(int value)
{

  switch (value)
  {
    case 0:
      multiplicateurFrais += StaticRandomizer::addRandomDouble(8);
      multiplicateurGain -= StaticRandomizer::addRandomDouble(8);
      return nom + " subit une nouvelle greve.";
      break;
    case 1:
      multiplicateurGain += 0.10 - StaticRandomizer::addRandomDouble(20);
      return "Pour " + nom + ", c'est l'heure des presidentielles.";
      break;
    case 2:
      multiplicateurFrais += 0.05 + StaticRandomizer::addRandomDouble(15);
      return "Face a la crise ecologique " + nom + " impose de nouvelles taxes sur les deplacements.";
      break;
    case 3:
      multiplicateurFrais -= 0.05 + StaticRandomizer::addRandomDouble(15);
      return nom + " s'ouvre au commerce internationnal.";
      break;
    case 4:
      multiplicateurFrais += 0.10 + StaticRandomizer::addRandomDouble(10);
      multiplicateurGain += 0.10 + StaticRandomizer::addRandomDouble(10);
      return nom + " acceuillera les prochains Jeux Olympiques ! ";
      break;
    case 5:
      multiplicateurFrais += StaticRandomizer::addRandomDouble(4);
      multiplicateurGain -= StaticRandomizer::addRandomDouble(4);
      return nom + "; face a une nouvelle crise economique, le peuple descend les rues!";
      break;
    case 6:
      multiplicateurFrais -= StaticRandomizer::addRandomDouble(10);
      return nom + " de nouveaux ports viennent fluidifier les echanges";
      break;
    case 7:
      return "Les premiers hyper loop arrivent a " + nom;
      break;
    case 8:
      multiplicateurGain += 0.05 + StaticRandomizer::addRandomDouble(15);
      return nom + "; investie dans le marchee de l'e-sport!";
      break;
    case 9:
      multiplicateurGain -= 0.05 + StaticRandomizer::addRandomDouble(15);
      return nom + " premiers cas d'une nouvelle epidemie, la crise sanitaire semble innevitable!";
      break;
    case 10:
      multiplicateurFrais -= 0.05 + StaticRandomizer::addRandomDouble(15);
      return nom + " met l'intelligence artificielle au service des transports commerciaux";
      break;
    default:
      return "";
      break;
  }
}

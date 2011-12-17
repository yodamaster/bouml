
#include "UmlNode.h"
#include "File.h"
#include "UmlDeploymentView.h"

#include "UmlCom.h"
void UmlNode::import(File & f, UmlDeploymentView * p, const QCString & ste)
{
  QCString s;

  if (f.read(s) != STRING)
    f.syntaxError(s, " deployment node's name expected");

  QCString s2;
  QCString id;
  QCString dummy_ste;
  QCString doc;
  QDict<QCString> prop;
  int k;
  
  do {
    k = f.readDefinitionBeginning(s2, id, dummy_ste, doc, prop);
  } while (id.isEmpty());
    
  UmlNode * x;
  
  if (scanning) {
    if ((x = UmlBaseNode::create(p, s)) == 0) {
      UmlCom::trace("<br>cannot create deployment node '" + s + "' in " +
		    p->fullName());
      throw 0;
    }
    newItem(x, id);
    
    if (!doc.isEmpty())
      x->set_Description(doc);
    
    x->setProperties(prop);
    x->set_Stereotype(ste);
  }
  else if ((x = (UmlNode *) findItem(id, aNode)) == 0) {
    UmlCom::trace("<br>unknown deployment node '" + s + "' in " +
                  p->fullName());
    throw 0;
  }

  f.unread(k, s2);
  f.skipBlock();
}


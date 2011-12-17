
#include "UmlParameter.h"

#include "UmlClass.h"
#include "CppSettings.h"
QCString UmlParameter::cpp(unsigned rank) const {
  QCString s;
  int index;

  if ((type.type != 0) &&
      (CppSettings::classStereotype(type.type->stereotype()) == "enum")) {
    switch (dir) {
    case InputDirection:
      s = CppSettings::enumIn();
      break;
    case OutputDirection:
      s = CppSettings::enumOut();
      break;
    default:
      // can't be return
      s = CppSettings::enumInout();
      break;
    }
  }
  else {
    switch (dir) {
    case InputDirection:
      if (!type.explicit_type.isEmpty())
	s = CppSettings::builtinIn(type.explicit_type);
      if (s.isEmpty()) 
	s = CppSettings::in();
    case OutputDirection:
      if (!type.explicit_type.isEmpty())
	s = CppSettings::builtinOut(type.explicit_type);
      if (s.isEmpty()) 
	s = CppSettings::out();
      break;
    default:
      // can't be return
      if (!type.explicit_type.isEmpty())
	s = CppSettings::builtinInout(type.explicit_type);
      if (s.isEmpty()) 
	s = CppSettings::inout();
    }
  }
  
  if ((index = s.find("${type}")) != -1) {
    QCString t;
    
    t.sprintf("${t%u}", rank);
    s.replace(index, 7, t);
  }
  
  QCString p;
  
  p.sprintf(" ${p%u}${v%u}", rank, rank);
  return s + p;
}


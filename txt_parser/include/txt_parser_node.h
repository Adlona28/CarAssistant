#ifndef txtParser_h
#define txtParser_h

//#include "txtParserConfig.h"
//#include <dynamic_reconfigure/server.h>

class TxtParserNode {
  private:
    //Config _config;

  protected:
    void main_loop(void);

  public:
    //typedef txt_parser::txtParserConfig Config;
    TxtParserNode(void);
};

#endif

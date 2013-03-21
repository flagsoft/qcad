

    // ***** AUTOGENERATED CODE, DO NOT EDIT *****
    
            // ***** This class is not copyable.
        
        #ifndef RECMAFILEEXPORTERREGISTRY_H
        #define RECMAFILEEXPORTERREGISTRY_H

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RFileExporterRegistry.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class REcmaFileExporterRegistry {

        public:
      static  void init(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue create(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        registerFileExporter
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getFileExporter
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        getFilterStrings
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RFileExporterRegistry* getSelf(const QString& fName, QScriptContext* context)
    ;static RFileExporterRegistry* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    
#include <libconfig.h>

//this is libconfig
//this library is for the configuration file

struct configurationFile
{
        char portNum[16];
        int variance;
        int directive;
        char directory[32];
        
}; //this is used for the configuration file

int processConfigFile(struct configurationFile *config, char const *filePath)
{
        config_t configFile; //this is the config file
                config_setting_t *setting;
                config_init(&configFile);
                char const *str;
                
                        if(! config_read_file(&configFile, filePath))
                        {
                                        
                                        config_destroy(&configFile);
                                        return -1;
                        }
                        
                        //~ struct configurationFile config;
                        
                //~ config_destroy(&configFile); //this destroys the file
                //~ if(config_lookup_string(&configFile, "port", &str))
                        
                        
                        if (config_lookup_string(&configFile, "port", &str))
                        {
                        strcpy(config->portNum,str);
                           
                        }  
                        if (config_lookup_string(&configFile, "directive", &str))
                        {
                        //~ strcpy(config->directive,str);
                        config->directive = atoi(str);
                        
                        }
                        
                        if (config_lookup_string(&configFile, "directory", &str))
                        {
                        strcpy(config->directory,str);
                        
                        }
                        
                        if (config_lookup_string(&configFile, "variance", &str))
                        {
                        //~ strcpy(config->variance,str);
                        config->variance = atoi(str);
						}
                        
                        
                
                
        
        config_destroy(&configFile);
        return 1;
        
}



void defaultTheConfigFileData(struct configurationFile *config)
{
	int stringLength = 0;
	stringLength = strlen("65000");
	
	strcpy(config->portNum,"65000");
	config->portNum[stringLength] = '\0';
	config->variance = 500;
	config->directive = ROUND_ROBIN;
	stringLength = strlen("/home/cluster");
	strcpy(config->directory,"/home/cluster");
	config->directory[stringLength] = '\0';
	
}

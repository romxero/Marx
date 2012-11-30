#include <libconfig.h>

//this is libconfig
//this library is for the configuration file

struct configurationFile
{
        char portNum[16];
        int variance;
        int directive;
        int min_peers;
        char directory[32]; 
        int benchscore; //bench score
        
}; //this is used for the configuration file

int processConfigFile(struct configurationFile *config, char const *filePath)
{
	//this function processes the config file
        config_t configFile; //this is the config file
                config_setting_t *setting;
                config_init(&configFile);
                char const *str;
                
                        if( config_read_file(&configFile, filePath) != CONFIG_TRUE)
                        {
                                        //the givin file does not exist
                                        config_destroy(&configFile);
                                        return -1;
                        }
                        
                        //~ struct configurationFile config;
                        
                //~ config_destroy(&configFile); //this destroys the file
                //~ if(config_lookup_string(&configFile, "port", &str))
                        
                        int stringLength = 0; //the string length right here
                        
                        if (config_lookup_string(&configFile, "port", &str))
                        {
							stringLength = strlen(str); //get the string length
							strcpy(config->portNum,str); //copy
                           config->portNum[stringLength] += '\0'; //add terminating character
                        }  
                        if (config_lookup_string(&configFile, "directive", &str))
                        {
                        stringLength = strlen(str); //get the string length
                        config->directive = atoi(str);
                        
                        }
                        
                        if (config_lookup_string(&configFile, "directory", &str))
                        {
							stringLength = strlen(str); //get the string length
							strcpy(config->directory,str);
							config->directory[stringLength] += '\0'; //add terminating character
                        }
                        
                        if (config_lookup_string(&configFile, "variance", &str))
                        {
                        //~ strcpy(config->variance,str);
                        config->variance = atoi(str);
						}
						
                        if (config_lookup_string(&configFile, "min_peers", &str))
                        {
                        
                        config->min_peers = atoi(str);
						}
                        
                        if (config_lookup_string(&configFile, "benchscore", &str))
                        {
                        
                        config->benchscore = atoi(str);
						}
                        //~ 
                        
                
                
        
        config_destroy(&configFile); //destroy the config file buffer
        return 1;
        
}



void defaultTheConfigFileData(struct configurationFile *config)
{
	//this function copies default data to structure if no config file exists
	int stringLength = 0;
	stringLength = strlen("65000");
	strcpy(config->portNum,"65000");
	config->portNum[stringLength] = '\0';
	config->variance = 5;
	config->directive = ROUND_ROBIN;
	stringLength = strlen("/home/cluster");
	strcpy(config->directory,"/home/cluster");
	config->directory[stringLength] = '\0'; //terminate the string
	config->min_peers = 3; //minimum peers allowed to continue 
	config->benchscore = -1; //this will signify that no benchscore exists
}


int writeBenchScoreToConfig(struct configurationFile *config, char const *filePath)
{
				
				//this is used to write a bench score to config file
				config_t configFile; //this is the config file
                config_setting_t *setting;
                config_init(&configFile);
                config_setting_t *writeToBench = NULL;
                
                
                        if(! config_read_file(&configFile, filePath))
                        {
                                        //the givin file does not exist
                                        config_destroy(&configFile);
                                        return -1;
                        }
                        
						writeToBench = config_lookup(&configFile, "benchscore");
						
						
						if (writeToBench  == NULL)
						{
										//couldn't find the benchmark score in config file!
										config_destroy(&configFile);
                                        return -1;
							
						}
						
							char benchString[10]; //standard buffer for string
							int n = 0; //used to determine the length
							n = sprintf (benchString, "%d", config->benchscore); //add the score as a string
							benchString[n] += '\0'; //add terminating character
						
							config_setting_set_string (writeToBench, benchString); //set the string of the configuration file
						
                        //~ if (!(config_setting_set_string (config_setting_t * setting, const char * value)))
                        //~ {
							//~ 
							//~ 
						//~ }
                        
							
							config_write_file(&configFile, filePath); //writes back to the file
						
					        config_destroy(&configFile); //destroy the config file buffer
					        
					        
					        return 1; //things are sane here
}

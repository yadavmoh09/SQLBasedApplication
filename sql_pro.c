			#include<stdio.h>
			#include<string.h>
			#include<stdlib.h>
			#include <time.h> 

			char value[30];
			struct data{
				struct data *next;
				char cvalue[500];
			};
			struct cstruct{
					struct cstruct *next;
					char name[30];
					char type[30];
					char size[30];
					struct data *index;
			};
			struct table{
				struct table *next;
				char name[30];
				struct cstruct *index;
			};
			struct Database{
					struct Database *next;
					char name[30];
					struct table *index;
			};
			struct holder{
				char name[30];
				char data[30];
				struct holder *next;
			};
			
			struct Database *database_start=NULL;
			struct Database *Uses_database=NULL;
			
			void delay(int number_of_seconds) { 
				int milli_seconds = 1000 * number_of_seconds; 
				clock_t start_time = clock(); 
				while (clock() < start_time + milli_seconds) 
					; 
			} 
			
			void welcome()
			{
				printf("\t\t\t\t+======================== Hello I am mohit  ===========================+\n\n");
				printf("\n\nOpening a programe....");
				for(int i=1;i<=15;i+=1)
				{
					
					if(i%2==0)
						printf("\b/");
					else
						printf("\b\\");
					delay(1);
				}
				
				printf("\ryou can use `--help` command to get Help\n");
				printf("and can use `cls` command to clear screen\n");
				

			}
		    struct cstruct * findColumn(struct table *tbl,char columnName[]){
				
					for(struct cstruct *temp=tbl->index;temp!=NULL;temp=temp->next)
					{	
							if(strcmp(temp->name,columnName)==0)
							{
								return temp;
							}
					}
					return NULL;
			}
			void truncateTable(struct table *tbl){
					for(struct cstruct *temp=tbl->index;temp!=NULL;temp=temp->next)
					{
						struct data *tmp=temp->index;
						temp->index=NULL;
						free(tmp);
					}
			}
			int check_Duplicate(struct Database *database,struct table *tbl,char *entity_name,char *entity){
					if(strcmp(entity,"table")==0){
						for(struct table *temp=database->index;temp!=NULL;temp=temp->next)
						{
								if(strcmp(temp->name,entity_name)==0)
								{
									return 1;
								}
						}
						return 0;
					}
					else if(strcmp(entity,"database")==0){
						for(struct Database *db=database_start;db!=NULL;db=db->next)
						{
								if(strcmp(db->name,entity_name)==0)return 1;
						}						
						return 0;
					}
					else if(strcmp(entity,"column")==0){
						for(struct cstruct *temp=tbl->index;temp!=NULL;temp=temp->next)
						{
								if(strcmp(temp->name,entity_name)==0)
										return 1;
						}
						return 0;
					}
			}
			void selectSpecific_Column(struct cstruct *str,char *column){
				printf("\n");
				for(struct cstruct *temp=str;temp!=NULL;temp=temp->next)
				{
					if(strcmp(temp->name,column)==0)
					{
						printf("%s\n",temp->name);
						for(struct data *temp1=temp->index;temp1!=NULL;temp1=temp1->next)
						{
							printf("%s\n",temp1->cvalue);
						}
						return;
					}
				}
				printf("error:unknown column `%s`..\n",column);
			}
			int cheakColumnType(char type[]){
					if(strcmp(type,"varchar")==0)return 1;
					else if(strcmp(type,"text")==0)return 1;
					else if(strcmp(type,"number")==0)return 1;
					else return 0;
			}
			void renameTable(struct table *tbl,struct Database *database){
					char tbl_name[30];
					char prv_name[30];
					strcpy(prv_name,tbl->name);
					t:
					printf("New Table Name:");
					scanf("%s",tbl_name);
					if(check_Duplicate(database,NULL,tbl_name,"table"))
					{
						printf("\nerror: table name `%s` already exist",tbl_name);
						printf("\n");
						goto t;
					}
					strcpy(tbl->name,tbl_name);
					printf("\nTable name has been changed `%s` to `%s`\n",prv_name,tbl->name);
			}
			int findNumberOfRows(struct cstruct *temp1){
				if(temp1==NULL)return 0;
				int i=0;
				for(struct data *temp=temp1->index;temp!=NULL;temp=temp->next)
				{
						i++;
				}
				return i;
			}
			void help(){
				printf("\n+======================( Help )======================+\n\n");
				delay(1);
				printf("\t+=====+ About databases +=====+\n\n");
				delay(1);
				printf("1:create database database_name ---> Query to create New Database\n");
				printf("2:use database database_name    ---> Query to select perticuler Database\n");
				printf("3:drop database database_name 	---> Query to delete perticuler Database\n");
				printf("4:alter database name dbName to newName ---> Query to update Database Name\n");
				printf("5:show databases ---> Query to see all present database\n");
				printf("6:leave database ---> Query to Exit From selected Database\n");
				delay(1);

				printf("\n\n\t+=====+ About Tables +=====+\n\n");
				delay(1);
				printf("1:create table table_Name ---> Query to create new Table\n");
				printf("2:show tables ---> Query to see all present Tables\n");
				printf("3:show table tbl_Name ---> Query to see structure of table\n");
				printf("4:alter table tbl_Name ---> Query to alter perticuler table\n");
				printf("5:insert into tbl_Name ---> Query to insert Data into perticuler table\n");
				printf("6:drop table tbl_Name ---> Query to drop perticuler table\n");
				printf("7:select column_Name from tbl_Name ---> Query to see data of perticuler column of the table\n");
				printf("8:select * from tbl_Name ---> Query to see all the data of the table\n");
				printf("9:truncate tbl_Name ---> Query to Delete all data of a table\n");
			}
			int findDataBase(char arr[]){
					if(database_start==NULL)return 0;
					
					for(struct Database *temp=database_start;temp!=NULL;temp=temp->next)
					{
							if(strcmp(temp->name,arr)==0)return 1;
					}
					return 0;
			}
			int stringToInt(char arr[]){
						int  i, len;
						int result=0;
						len=strlen(arr);
						for(i=0; i<len; i++){
						result = result * 10 + ( arr[i] - '0' );
						}	
						return result;
			}
			void InsertIntoTable(struct table *tbl){
				for(struct cstruct *temp=tbl->index;temp!=NULL;temp=temp->next)
				{
					char size_char[30];
					
					strcpy(size_char,temp->size);
					
					int size=stringToInt(size_char);
					
					char writenLine[100];
					printf("\nvalue for %s = ",temp->name);
					gets(writenLine);
					
					if(strlen(writenLine)<=size)
					{
						struct data *dt=(struct data*)malloc(sizeof(struct data));
						
						strcpy(dt->cvalue,writenLine);
						
						if(temp->index==NULL)
						{
								dt->next=temp->index;
								temp->index=dt;
						}
						else{
							for(struct data *temp1=temp->index;temp1!=NULL;temp1=temp1->next)
							{
									if(temp1->next==NULL)
									{
										dt->next=temp1->next;
										temp1->next=dt;
										break;
									}
							}
						}
					}
					else{
						printf("error:Size are too long...");
						return;
					}
				}
				printf("\nQuery excecuted successfully...");
			}
			void dropDatabase(char *ptr){
				int i=1;
				for(struct Database *temp=database_start,*temp1;temp!=NULL;temp=temp->next,i++)
				{
						if(strcmp(temp->name,ptr)==0)
						{
									if(i==1)
									{
											database_start=temp->next;
									}
									else{
										temp1->next=temp->next;
									}
									free(temp);
									printf("\nDatabase has been Droped...");
									return;
						}
						temp1=temp;
				}
				printf("\nerror:unknown database...");
						
			}
			void modifyColumn(struct table *tbl){
				
						int i=1;
						char choice[30];
						char name[30];
						int j=1;
						printf("+============+ Colums in %s +============+\n\n",tbl->name);
						for(struct cstruct *temp=tbl->index;temp!=NULL;temp=temp->next)
						{
								printf("%d. Modify %s\n",i++,temp->name);
						}
						printf("Column Name:");
						scanf("%s",choice);
						C:
						printf("\nNew Column Name:");
						scanf("%s",name);
						if(check_Duplicate(NULL,tbl,name,"column"))
						{
							printf("\nerror: column name `%s` already exist",name);
							goto C;
						}
						for(struct cstruct *temp=tbl->index,*temp1=tbl->index;temp!=NULL;temp=temp->next,j++)
						{
								if(strcmp(temp->name,choice)==0)
								{
									strcpy(temp->name,name);
										
										printf("ALTER TABLE `%s` CHANGE `%s` `%s` %s(%s)  executed successfully",tbl->name,choice,name,temp->type,temp->size);
										break;
								}
								temp1=temp;
						}
			}
			void showQuery(struct table *tbl){
					printf("(");
					for(struct cstruct *temp=tbl->index;temp!=NULL;temp=temp->next)
					{
							printf("%s %s(%s)",temp->name,temp->type,temp->size);
							if(temp->next!=NULL)
								printf(",");
								
					}
					printf(")'");
			}
			struct table* findTable(char *ptr,struct Database *database){
					for(struct table *temp=database->index;temp!=NULL;temp=temp->next)
					{
							if(strcmp(temp->name,ptr)==0)
							{
									return temp;
							}
					}
					return NULL;
			}
			void showtblStructure(struct table *tbl){
				if(tbl!=NULL)
				{
						printf("+============+ %s structure +============+\n",tbl->name);
						printf("Column Name\t\ttype\t\t\tsize\n");
						for(struct cstruct *temp=tbl->index;temp!=NULL;temp=temp->next)
						{
								printf("%s",temp->name);
								printf("\t\t\t%s",temp->type);
								printf("\t\t\t%s\n",temp->size);
						}
				}else{
					printf("\nerror:unkown table name");
				}
			}
			void showMessage(){
					printf("\n%sWrite Query:>",value);
			}
			void dropColumn(struct table *tbl){
						int i=1;
						char choice[30];
						int j=1;
						printf("+============+ Colums in %s +============+\n\n",tbl->name);
						for(struct cstruct *temp=tbl->index;temp!=NULL;temp=temp->next){
								printf("%d. Drop %s\n",i++,temp->name);
						}
						printf("Column Name:");
						scanf("\n%s",choice);
						for(struct cstruct *temp=tbl->index,*temp1=tbl->index;temp!=NULL;temp=temp->next,j++){
								if(strcmp(temp->name,choice)==0)
								{
										if(j==1)
										{
											tbl->index=temp->next;
										}
										else{
											temp1->next=temp->next;
										}
										printf("ALTER TABLE `%s` Drop `%s`	 executed successfully",tbl->name,choice);
										free(temp);
										break;
								}
								temp1=temp;
						}
			}
			void addColumn(struct table *tbl){
				char choice;
				char cname[30];
				char ctype[30];
				char csize[30];
				char garbage;
				while(1){
						printf("\nAdd Column ? (Y|n):");
						scanf("\n%c",&choice);
						if(choice=='Y' | choice=='y'){
								C:
								printf("\n\t\tColumn Name:");
								scanf("%s",cname);
								if(check_Duplicate(NULL,tbl,cname,"column")){
									printf("\n\t\t error: Column `%s` already exist...\n",cname);
									goto C;
								}
								M:
								printf("\n\t\tColumn type:");
								scanf("%s",ctype);
								if(!cheakColumnType(ctype)){
									printf("\n\t\terror:Invalid Column type: `%s` you can use `text`,`number`,`varchar` as column type...\n",ctype);
									goto M;
								}
								printf("\n\t\tColumn size:");
								scanf("%s",csize);
								scanf("%c",&garbage);
								struct cstruct *temp=(struct cstruct*)malloc(sizeof(struct cstruct));
								strcpy(temp->name,cname);
								strcpy(temp->type,ctype);
								strcpy(temp->size,csize);
								temp->index=NULL;
								if(tbl->index==NULL){
										temp->next=tbl->index;
										tbl->index=temp;
								}
								else{
										for(struct cstruct *temp1=tbl->index;temp1!=NULL;temp1=temp1->next)
										{
												if(temp1->next==NULL)
												{
														temp->next=temp1->next;
														temp1->next=temp;
														break;
												}
										}
								}
								
								int i=findNumberOfRows(tbl->index);
								if(i>0){
									int j=0;
										while(j<i){
											struct data *dta=(struct data *)malloc(sizeof(struct data));
											strcpy(dta->cvalue,"0");
											if(temp->index==NULL)
											{
													dta->next=temp->index;
													temp->index=dta;
											}						
											else{
												for(struct data *tmp=temp->index;tmp!=NULL;tmp=tmp->next)
												{
														if(tmp->next==NULL)
														{
															dta->next=tmp->next;
															tmp->next=dta;
															break;
														}
												}
											}
											j++;
										}										
								}
						}
						else{	
							break;
						}
				}
			}
			void dropTable(struct Database *database,char *ptr){
					if(database->index==NULL)
					{
						printf("\nthere is no table...\n");
					}
					else{
						int i=0;
						for(struct table *temp=database->index,*last_index=database->index;temp!=NULL;temp=temp->next,i++)
						{
								if(strcmp(temp->name,ptr)==0)
								{
									char choice;
									char tmp;
									printf("Do you really want to execute \"drop TABLE %s\" ?(y|N) :",ptr);
									scanf("%c",&choice);
									scanf("%c",&tmp);
									if(choice=='Y' | choice=='y')
									{
										if(i==0)
										{
											database->index=temp->next;
										}
										else
										{
											last_index->next=temp->next;
										}
										free(temp);
										printf("\ntable droped successfully...\n");
										return;
									}
									else{
										return;
									}
								}
								last_index=temp;
						}
						printf("\nTable not found...\n");
					}
			}
			void showTable(struct Database *database){	
				if(database->index==NULL)
				{
					printf("there is no any table...\n");
				}
				else{
					printf("+===============+ tables +===============+");
						for(struct table *temp=database->index;temp!=NULL;temp=temp->next)
						{
								printf("\n%s",temp->name);
						}
					printf("\n+=========================================+");
				}
				
					
			}
			void createTable(struct Database *database,char *ptr){
						if(check_Duplicate(database,NULL,ptr,"table")){
								printf("\nerror: table `%s` already exist..\n",ptr);
								return;}
							
						struct table *newTable=(struct table*)malloc(sizeof(struct table));
						strcpy(newTable->name,ptr);
						
					if(database->index==NULL)
					{
						newTable->next=database->index;
						database->index=newTable;
						newTable->index=NULL;
						addColumn(newTable);
						printf("'create table %s",ptr);
						showQuery(newTable);
						printf("executed successfully");
					}
					else{
						for(struct table *temp=database->index;temp!=NULL;temp=temp->next)
						{
								if(temp->next==NULL)
								{
											newTable->next=NULL;
											temp->next=newTable;
											newTable->index=NULL;
											addColumn(newTable);
											printf("'create table %s",ptr);
											showQuery(newTable);
											printf(" executed successfully");
											break;
								}
						}
						
					}
			}
			void useDatabase(char *ptr){
				if(Uses_database!=NULL){
						printf("error:you are using '%s' database plz go outside from this database to use another.using 'leave database' command...\n",Uses_database->name);
				}
				else{
						if(database_start==NULL)
						{	
								printf("error:Unknown database '%s'\n",ptr);
						}
						else{
								for(struct Database *temp=database_start;temp!=NULL;temp=temp->next)
								{
										if(strcmp(temp->name,ptr)==0)
										{
												Uses_database=temp;
												printf("\nselected database %s\n",ptr);
												// strcpy(value,strcat(ptr,"/"));
												return;
										}
								}	
								printf("error:Unknown database '%s'\n",ptr);
						}
				}
			}
			struct Database* checkSelectedDataBase(){
					if(Uses_database==NULL)
					{
							return NULL;
					}
					else{
						return Uses_database;
					}
					
				
			}
			void showDataBase(){
				if(database_start==NULL)
				{
						printf("Database Not Found...\n");
				}
				else{
					printf("\n");
					printf("+================+ Database list +================+");
					for(struct Database *temp=database_start;temp!=NULL;temp=temp->next)
					{
						printf("\n%s",temp->name);
					}
					printf("\n+=================================================+\n");
					}
			}
			void createDatabase(char *ptr){
				
									if(check_Duplicate(NULL,NULL,ptr,"database"))
									{
										printf("\nerror:database `%s` already exist..\n",ptr);
										return;
									}
									struct Database *database_temp=(struct Database*)malloc(sizeof(struct Database));
									strcpy(database_temp->name,ptr);
									if(database_start==NULL)
									{
													database_temp->next=database_start;
													database_temp->index=NULL;
													database_start=database_temp;
													printf("Database has been created successfully..\n");
										}
									else{
													
												for(struct Database *temp=database_start;temp!=NULL;temp=temp->next)
												{
														if(temp->next==NULL)
														{
																database_temp->next=NULL;
																database_temp->index=NULL;
																temp->next=database_temp;
																printf("Database has been created successfully..\n");
																break;
																
														}
												}
										}
			}
			int countNumberOfValuesInColumn(struct table *tbl,char value[],char columnName[]){
					int counter=0;
					struct cstruct *column=findColumn(tbl,columnName);
					for(struct data *dta=column->index;dta!=NULL;dta=dta->next){
						if(strcmp(dta->cvalue,value)==0)
						{
							counter++;
						}
					}
					return counter;
			}
			void updateData(struct table *tbl,struct holder *holder_data,char where[],char CValue[]){	
						int count=countNumberOfValuesInColumn(tbl,CValue,where);
						
						printf("\n%d number of row's updated\n",count);
						for(;holder_data!=NULL;holder_data=holder_data->next)
						{
								printf("\n name : %s and value : %s ",holder_data->name,holder_data->data);
						}
			}
			void Update_Data_Of_Table(struct table *tbl,char where[],char CValue[]){
				struct holder *dt_start=NULL;
				
				for(struct cstruct *temp=tbl->index;temp!=NULL;temp=temp->next)
				{
					if(strcmp(temp->name,where)==0)
						continue;
						
					char size_char[30];
					
					strcpy(size_char,temp->size);
					
					int size=stringToInt(size_char);
					
					char writenLine[100];
					char garbage[2];
					char choice[10];
					printf("\nWant Update %s ? (Y|N):",temp->name);
					gets(choice);
					
					if(!(strcmp(choice,"Y")==0 || strcmp(choice,"y")==0))
						continue;
					
					
					printf("\nvalue for %s = ",temp->name);
					gets(writenLine);
					
					if(strlen(writenLine)<=size)
					{
						struct holder *dt=(struct holder *)malloc(sizeof(struct holder));
						
						strcpy(dt->data,writenLine);
						strcpy(dt->name,temp->name);
						
						if(dt_start==NULL)
						{
								dt->next=dt_start;
								dt_start=dt;
						}
						else{
							for(struct holder *temp1=dt_start;temp1!=NULL;temp1=temp1->next)
							{
									if(temp1->next==NULL)
									{
										dt->next=temp1->next;
										temp1->next=dt;
										break;
									}
							}
						}
					}
					else{
						printf("error:Size are too long...");
						return;
					}
				}
				updateData(tbl,dt_start,where,CValue);
				
			}
			int findValue(struct data *temp,char value[]){
					for(;temp!=NULL;temp=temp->next)
					{
							if(strcmp(temp->cvalue,value)==0)
							{
								return 1;
							}
					}
					return 0;
			}
			void readQuery(char str[]){
					char delim[] = " ";
					char *ptr = strtok(str, delim);
					while(ptr != NULL){
						if(strcmp(ptr,"create")==0){
								ptr = strtok(NULL, delim);
								if(strcmp(ptr,"database")==0)
								{
									ptr = strtok(NULL, delim);
									struct Database *currentDatabase = checkSelectedDataBase();
									if(currentDatabase==NULL)
										createDatabase(ptr);
									else
										printf("error:Please leave current database first by \"leave database command\"\n");
								}
								else if(strcmp(ptr,"table")==0){
									
									ptr = strtok(NULL, delim);
									struct Database *currentDatabase = checkSelectedDataBase();
									if(currentDatabase!=NULL)
									{
										createTable(currentDatabase,ptr);
									}
									else{
										printf("error:Database Not Found...");
									}
								}
						}
						else if(strcmp(ptr,"show")==0){
							
								ptr = strtok(NULL, delim);
								if(strcmp(ptr,"databases")==0)
								{
									showDataBase();
								}else if(strcmp(ptr,"tables")==0)
								{
									struct Database *database=checkSelectedDataBase();
									if(database!=NULL)
									{
										showTable(database);
									}
								}else if(strcmp(ptr,"table")==0)
								{
									ptr = strtok(NULL, delim);
									struct Database *database=checkSelectedDataBase();
									if(database!=NULL)
									{
										showtblStructure(findTable(ptr,database));
									}
								
										
								}
							
						
						}
						else if(strcmp(ptr,"use")==0){
							
								ptr = strtok(NULL, delim);
								if(strcmp(ptr,"database")==0)
								{
								ptr = strtok(NULL, delim);
									useDatabase(ptr);
								}
						
						}
						else if(strcmp(ptr,"leave")==0){
								ptr = strtok(NULL, delim);	
								if(strcmp(ptr,"database")==0)
								{	
										if(Uses_database==NULL)
												printf("Database was not selected...\n");
										
										else{
										Uses_database=NULL;
										printf("you are outside of the database...\n");
										strcpy(value,"");
										}
										
								}
						}
						else if(strcmp(ptr,"drop")==0){
								ptr = strtok(NULL, delim);	
								if(strcmp(ptr,"table")==0)
								{
										ptr = strtok(NULL, delim);	
										struct Database *database=checkSelectedDataBase();
										if(database!=NULL)
										{
											dropTable(database,ptr);
										}
										else
											printf("error:Database Not Found...");
								}else if(strcmp(ptr,"database")==0)
								{
										ptr = strtok(NULL, delim);	
										struct Database *database=checkSelectedDataBase();
										if(database==NULL)
										{
												if(findDataBase(ptr))
												{
												char choice;
												printf("\n You are about to DESTROY a complete database! Do you really want to execute \"DROP DATABASE ` %s `\"? (y|N) : ",ptr);
												scanf("\n%c",&choice);
												if(choice=='Y' | choice=='y')
												{
												dropDatabase(ptr);
												}
												}
												else
													printf("Can't drop database '%s'; database doesn't exist\n",ptr);
										}
										else{
											printf("error:your are using database please Go outside to run this query..\n");
										}
								}
									
						}
						else if(strcmp(ptr,"alter")==0){
							ptr = strtok(NULL, delim);	
								if(strcmp(ptr,"table")==0)
								{
										ptr = strtok(NULL, delim);	
										struct Database *database=checkSelectedDataBase();
										if(database!=NULL)
										{
											struct table *tbl=findTable(ptr,database);
											if(tbl!=NULL)
											{
															int choice;
															char garbage;
															printf("\n1.Add Column");
															printf("\n2.Modify  Column");
															printf("\n3.Drop Column");
															printf("\n4.Rename Table");
															printf("\nchoice:");
															scanf("%d",&choice);
															scanf("%c",&garbage);
															switch(choice)
															{
																	case 1:addColumn(tbl);
																			break;
																	case 2:modifyColumn(tbl);
																			break;
																	case 3:dropColumn(tbl);
																			break;
																	case 4:renameTable(tbl,database);
																			break;
																	default:printf("\nerror:choosen option is not Available...");		
																			break;
															}
										
											}
											else{
												printf("\nerror:unknown Table %s",ptr);
											}
										}
									
								}	
								else if(strcmp(ptr,"database")==0){
										ptr = strtok(NULL, delim);
										if(strcmp(ptr,"name")==0)
										{
											ptr = strtok(NULL, delim);
											if(findDataBase(ptr))
											{
													for(struct Database *temp=database_start;temp!=NULL;temp=temp->next)
													{
															if(strcmp(temp->name,ptr)==0)
															{
																	ptr = strtok(NULL, delim);
																	ptr = strtok(NULL, delim);
																	if(check_Duplicate(NULL,NULL,ptr,"database"))
																	{
																		printf("\nerror: Database name `%s` already exist\n",ptr);
																		break;
																	}
																	strcpy(temp->name,ptr);
																	printf("Database name has been changed..\n");
															}
													}
											}else{
												printf("error:Database `%s` does not exist..\n",ptr);
											}
											
										
										}
										else	
											printf("error:written query does not exist..\n");
											
								}
						}
						else if(strcmp(ptr,"insert")==0){
							ptr = strtok(NULL, delim);
							if(strcmp(ptr,"into")==0)
							{
									ptr = strtok(NULL, delim);
									struct Database *database=checkSelectedDataBase();
									if(database!=NULL)
									{
											struct table *tbl=findTable(ptr,database);
											if(tbl!=NULL)
											{	
												InsertIntoTable(tbl);
											}
											else{
												printf("error:unknown table '%s'",ptr);
											}
										
									}
									else{
										printf("\nerror:Database not Found..");
									}
								
							}
						}
						else if(strcmp(ptr,"select")==0){
									char *column = strtok(NULL, delim);
									char *syntax=strtok(NULL, delim);
									char *tble=strtok(NULL, delim);
									
									if(strcmp(column,"*")==0)
									{
											if(strcmp(syntax,"from")==0)
											{
													ptr = strtok(NULL, delim);
													struct Database *database=checkSelectedDataBase();
													if(database!=NULL)
													{	
														struct table *tbl=findTable(tble,database);
														if(tbl!=NULL)
														{
															struct cstruct *str=tbl->index;
															printf("\n");
															for(struct cstruct *temp=str;temp!=NULL;temp=temp->next)
															{
																printf("%s\t",temp->name);
															}
															printf("\n");
															int i=findNumberOfRows(str);
															for(int j=0;j<i;j++)
															{
																	for(struct cstruct *column=str;column!=NULL;column=column->next)
																	{
																			struct data *temp=column->index;
																			if(temp==NULL)
																				continue;
																			for(int k=0;k<j;k++)
																			{
																				if(temp==NULL)
																				{
																					break;
																				}
																				temp=temp->next;
																			}
																			printf("%s\t",temp->cvalue);
																	}
																	printf("\n");
															}
														}
														else{
															printf("\nerror:unkown table %s",tble);
															return;
														}
													}
													else{
														printf("\nerror:Database not found...");
														return;
													}
														
														
											}
											else{
												printf("\nYou have an error in your SQL syntax;");
											}
									}
									else{
											if(!strcmp(syntax,"from")==0){
												printf("\nsyntax error:invalid Syntax\n");
												return;}
													
													struct Database *database=checkSelectedDataBase();
													if(database!=NULL)
													{	
														struct table *tbl=findTable(tble,database);
														if(tbl!=NULL)
														{
															struct cstruct *str=tbl->index;
															
															selectSpecific_Column(str,column);
														}
														else{
															printf("\nerror:unkown table %s",tble);
															return;
														}
													}
													else{
														printf("\nerror:Database not found...");
														return;
													}
														
									}
						}
						else if(strcmp(ptr,"--help")==0){
													help();
													}
						else if(strcmp(ptr,"cls")==0){
							system("cls");
						}
						else if(strcmp(ptr,"truncate")==0){
							
								char *tble=strtok(NULL, delim);
								struct Database *database=checkSelectedDataBase();
								if(database!=NULL)
								{
									struct table *tbl=findTable(tble,database);
									if(tbl!=NULL)
									{
										char choice;
										printf("\nYou are about to TRUNCATE a complete table! Do you really want to execute 'TRUNCATE `%s`.`%s`'? (y|N) : ",database->name,tbl->name);
										scanf("%c",&choice);
										if(choice=='Y' || choice=='y')
										{
											truncateTable(tbl);
											printf("\ntable `%s` has been truncated successfully...\n",tbl->name);
											scanf("%c");
										}
										else{
											scanf("%c");
										}
									}
									else
										printf("\nerror:unknown table `%s`\n",tble);
								}else{
									printf("\nerror:Database not found...\n");
								}
						}
						else if(strcmp(ptr,"update")==0){
								char *tbl_Name = strtok(NULL, delim);
								char *where_clmnName;
								char *CValue;
									ptr = strtok(NULL, delim);
									if(strcmp(ptr,"set")==0)
									{	
											ptr = strtok(NULL, delim);
											if(strcmp(ptr,"where")==0)
											{
													where_clmnName = strtok(NULL, delim);
													ptr = strtok(NULL, delim);
													if(strcmp(ptr,"=")==0)
													{
														CValue = strtok(NULL, delim);
														ptr = strtok(NULL, delim);
															if(ptr==NULL)
															{
																
																	struct Database *database=checkSelectedDataBase();
																	if(database!=NULL)
																	{
																		struct table *tbl=findTable(tbl_Name,database);
																		if(tbl!=NULL)
																		{
																				struct cstruct *temp=findColumn(tbl,where_clmnName);
																				if(temp!=NULL)
																				{
																						if(findValue(temp->index,CValue))
																						{
																							Update_Data_Of_Table(tbl,where_clmnName,CValue);
																							
																						}else
																							printf("\nerror:value did't find for `%s` = `%s` \n",where_clmnName,CValue);
																					
																				}else 
																					printf("\nerror:unkwon Column `%s` \n",where_clmnName);
																		}
																		else
																			printf("\nerror:unkwon table `%s` \n",tbl_Name);
																	}
																	else printf("\nerror: database not found...\n");
															}else printf("\nerror: unkown Query....\n");
																
													}else
													printf("\nerror: unkown Query....\n");
													
											}
											else
													printf("\nerror: unkown Query....\n");
										
									}	
									else
										printf("\nerror: unkown Query....\n");
								
							
						}
						ptr = strtok(NULL, delim);
					}
			}
			int main(){
				char str[50];
				strcpy(value,"");
				
				welcome();
				while(1)
				{
					showMessage();
					gets(str);
					readQuery(str);
				}
			}
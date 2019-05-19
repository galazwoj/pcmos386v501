#include "rsa.h"

char *field_name[] = {
	 "unknown"
	,"CH_FIELD"	    
	,"I2_FIELD"            
	,"IL_FIELD"            
	,"FLOAT_FIELD"         
	,"TIME_FIELD"          
	,"NUMERIC_DATE_FIELD"  
	,"STRING_DATE_FIELD"   
	,"HX_FIELD"            
	,"HL_FIELD"            
	,"HASH_FIELD"          
	,"U2_FIELD"            
	,"UL_FIELD"            
	};

void read_proc(int field_type)
{
	int result = 0;
        char buf[82];
	int size; 
	struct DATETIME *dt; 

	buf[0] ='\0';
	switch (field_type)
	{
		case TIME_FIELD:  
		case NUMERIC_DATE_FIELD:
			size = 8;
			break;
		case STRING_DATE_FIELD:
			size = 9;
			break;
		default:
			size = 5;
	}

	result = readed(4, 0 , field_type, size, _$bar_color, buf);	
	switch (field_type)
	{
		case CH_FIELD:	   	// anything 
			printf("\nresult = %d, (%c)", result, buf);
			break;
		case I2_FIELD:     	// signed integer, digits      
			printf("\nresult = %d, (%d)", result, *(int *)buf);
			break;
		case IL_FIELD:         	// signed long, digits   
			printf("\nresult = %d, (%ld)", result, *(long *)buf);
			break;
		case FLOAT_FIELD:     	// float, digits 	
			printf("\nresult = %d, (%f)", result, *(float *)buf);
			break;
		case TIME_FIELD:     	// hh:mm:ss   
			dt = (struct DATETIME *)buf;        
			printf("\nresult = %d, (%d:%d:%d)", result, dt->hour, dt->minute, dt->second);
			break;
		case STRING_DATE_FIELD:	// yy-month-dd   
			dt = (struct DATETIME *)buf;        
			printf("\nresult = %d, (%d:%d:%d)", result, dt->year, dt->month, dt->day);
			break;
		case NUMERIC_DATE_FIELD:// mm/dd/yy	 	 
			dt = (struct DATETIME *)buf;        
			printf("\nresult = %d, (%d:%d:%d)", result, dt->year, dt->month, dt->day);
			break;
		case HX_FIELD:            
			printf("\nresult = %d, (%x)", result, *(int *)buf);
			break;
		case HL_FIELD:            
			printf("\nresult = %d, (%lx)", result, *(long *)buf);
			break;
		case HASH_FIELD:          
			printf("\nresult = %d, (%s)", result, buf);
			break;
		case U2_FIELD:            
			printf("\nresult = %d, (%u)", result, *(unsigned int *)buf);
			break;
		case UL_FIELD:            
			printf("\nresult = %d, (%lu)", result, *(unsigned long *)buf);
			break;
		default:
			printf("\nunknownn");
	}
	printf(", %s\n",(field_type > UL_FIELD)? field_name[0] : field_name[field_type]);	
}

int main(void)
{
	read_proc(CH_FIELD);	
	read_proc(I2_FIELD);	
	read_proc(IL_FIELD);	
	read_proc(FLOAT_FIELD);	
	read_proc(TIME_FIELD);	
	read_proc(STRING_DATE_FIELD);	
	read_proc(NUMERIC_DATE_FIELD);	
	read_proc(HX_FIELD);	
	read_proc(HL_FIELD);	
	read_proc(HASH_FIELD);	
	read_proc(U2_FIELD);	
	read_proc(UL_FIELD);	// there is a bug in the original rsa code 

	return 0;
}

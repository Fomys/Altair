/* cpu.c example cpu-description file */
/* (c) in 2002 by Volker Barthelmann */
/* (c) in 2020 by Samy Meguenoun */
#include <stdlib.h>
#include "vasm.h"

char *cpu_copyright="vasm Altair K1 cpu backend 0.1 (c) 2020 Samy Meguenoun";


char *cpuname="AltairK1";
int bitsperbyte=8;
int bytespertaddr=4;
int k1ext = 0x0;


mnemonic mnemonics[]={
#include "opcodes.h"

};

int mnemonic_cnt=sizeof(mnemonics)/sizeof(mnemonics[0]);
static char current_ext;   

char *parse_instruction(char *s,int *inst_len,char **ext,int *ext_len,
                        int *ext_cnt)
/* parse instruction and save extension locations */
{
    char *inst = s;
    int cnt = *ext_cnt;

    if (*s == '.')  /* allow dot as first char */
        s++;
    while (*s && *s!='.' && !isspace((unsigned char)*s))
        s++;
    *inst_len = s - inst;

    while (*s=='.' && cnt<MAX_QUALIFIERS)
    {
        s++;
        ext[cnt] = s;
        while (*s && *s!='.' && !isspace((unsigned char)*s))
            s++;
        ext_len[cnt] = s - ext[cnt];
        if (ext_len[cnt] <= 0)
            cpu_error(34);  /* illegal opcode extension */
        else
            cnt++;
    }
    *ext_cnt = cnt;

    if (cnt > 0)
        current_ext = tolower((unsigned char)ext[0][0]);
    else
        current_ext = '\0';

    return s;
}


int set_default_qualifiers(char **q,int *q_len)
/* fill in pointers to default qualifiers, return number of qualifiers */
{
    q[0] = "w";
    q_len[0] = 1;
    return 1;
}

/* Does not do much useful parsing yet. */
int parse_operand(char *p,int len,operand *op,int requires)
{
    op->type = requires;
    op->value = NULL;
    char arg[32];
    int i;

    //imm[rxx]
    if(requires == OP_IMR )
    {
        i = 0;
        
        while(p[i] != '[')
        {
            arg[i] = p[i];
            i++;
        }

        len -= i;
        if(len < 4) return 0;
        if(len > 6) return 0;

        if( !(p[i+1] == 'r' || p[i+1] == 'R') )
            return 0;


        if( (len == 5) && (p[i+3] == '+') )
        {
            op->type |= 0x100;
            len--;
        }

        if( (len == 6) && (p[i+4] == '+') )
        {
            op->type |= 0x100;
        }

        arg[0] = p[i+2];
        if(len == 4)
        {
            arg[1] = 0;


        }else
        {
            arg[1] = p[i+3];
            arg[2] = 0;
        }

        op->reg = atoi(arg);

        op->value = parse_expr(&p);

        return 1;
    }
    
    //Register VP0-VP63
    if(requires == OP_VP )
    {
        
        if( (len < 3) || (len > 5) ) return 0;
        if( !(p[0] == 'v' || p[0] == 'V') )
            return 0;

        if( !(p[1] == 'p' || p[1] == 'P') )
            return 0;

        
        arg[0] = p[2];
        if(len == 3)
        {
            arg[1] = 0;
        }
        {
        	if( (p[3] >= '0') && (p[3] <= '9') )
            	arg[1] = p[3];
            else
            {
            	op->val = 'x'-p[3]+1;
            	arg[1] = 0;
            }

            arg[2] = 0;

            if(!( (p[4] >= '0') && (p[4] <= '9') ))
            {
            	op->val = 'x'-p[3]+1;            	
            }
        }

        op->reg = atoi(arg);
        if(op->reg > 63) return 0;

        return 1;
    }


    //Register R0-R63
    if(requires == OP_REG )
    {
        if( (len < 2) || (len > 3) ) return 0;
        if( !(p[0] == 'r' || p[0] == 'R') )
            return 0;
        
        
        arg[0] = p[1];
        if(len == 2)
        {
            arg[1] = 0;
        }
        {
            arg[1] = p[2];
            arg[2] = 0;
        }
        op->reg = atoi(arg);
        if(op->reg > 63) return 0;
        return 1;
    }

    //Register LR
    if(requires == OP_RLR )
    {
        if(len != 2) return 0;
        if( !(p[0] == 'l' || p[0] == 'L') )
            return 0;

        if( !(p[1] == 'r' || p[1] == 'R') )
            return 0;
        
        return 1;
    }

    //Register BR
    if(requires == OP_RBR )
    {
        if(len != 2) return 0;
        if( !(p[0] == 'b' || p[0] == 'B') )
            return 0;

        if( !(p[1] == 'r' || p[1] == 'R') )
            return 0;
        
        return 1;
    }

   
    //Immediate
    if( (requires >= OP_IMM) && (requires <= OP_IM4) )
    {
        op->val = atoi(p);
        op->fval = atof(p);
        op->value = parse_expr(&p);

        //printf("%d\n",op->val);
        
        return 1;
    }


    return 0;
}

char *outbin(unsigned int n)
{
    static char buffer [1+sizeof (unsigned int)*8] = { 0 };
    unsigned int bit = 0 ;
    int i;
    for (i = 0 ; i < sizeof (unsigned int)*8; i++)
    {
        bit = n&1;
        buffer[i] = bit+'0';
        n = n>>1;
    }
    buffer[i] = '\0';

    return buffer;
}

void printbin(unsigned int n)
{
    unsigned int bit = 0 ;
    for (int i = 0 ; i < sizeof(unsigned int)*8 ; i++)
    {
        bit = n&1;
        printf("%d", bit) ;
        if(((i+1)&7) == 0) printf(" ") ;
        n = n>>1;
    }
    printf("\n");
}

/* Convert an instruction into a DATA atom including relocations,
   if necessary. */
dblock *eval_instruction(instruction *p,section *sec,taddr pc)
{
    
    dblock *db=new_dblock();


    unsigned char *d;
    int opcode = (mnemonics[p->code].ext.opcode);
    int val,val2,ret,byte = 0,plus = 0,type;
    operand operand1,operand2,operand3;

    //printf("%d\n",pc);


    int k1ext = 0x02;
    int inst = opcode&0x3;


    if(p->qualifiers[0] != 0)
    {
        char *ext = p->qualifiers[0];
        int i = 0,n;

        while(p->qualifiers[0][i]) i++;
        n = i;

        if(ext[0] == 'a') k1ext = 0;
        if(ext[0] == '1') k1ext = 1;
        if(ext[0] == '2') k1ext = 2;
        if(ext[0] == '3') k1ext = 3;


        if(ext[0] == 'b') k1ext = 0;
        if(ext[0] == 'w') k1ext = 1;
        if(ext[0] == 'l') k1ext = 2;
        if(ext[0] == 'q') k1ext = 3;

        if(ext[0] == 'h') k1ext = 0;
        if(ext[0] == 's') k1ext = 1;
        
        if(ext[0] == 'x') k1ext = 0;
        if( (n == 2) && (ext[1] == 'y') ) k1ext = 1;
        if( (n == 3) && (ext[2] == 'z') ) k1ext = 2;
        if( (n == 4) && (ext[3] == 'w') ) k1ext = 3;

    }
    
    if(p->op[0] != NULL)
        operand1 = *(p->op[0]);
    else
        operand1.type = OP_VOID;

    if(p->op[1] != NULL)
        operand2 = *(p->op[1]);
    else
        operand2.type = OP_VOID;
        
    if(p->op[2] != NULL)
        operand3 = *(p->op[2]);
    else
        operand3.type = OP_VOID;

    if(operand1.type&0x100) plus |= 1;
    if(operand2.type&0x100) plus |= 1;

    operand1.type &= 0xFF;
    operand2.type &= 0xFF;


    //IMR1,IMR2 AGU
    if(operand1.type == OP_IMR && operand2.type == OP_IMR && operand3.type == OP_VOID)
    {
        eval_expr(operand1.value,&val,sec,pc);
        operand1.val = val&0xFFF;

        eval_expr(operand2.value,&val,sec,pc);
        operand2.val = val&0xFFF;

        if(inst == 0x00)
        {
            operand1.reg -= 58;
            operand2.reg -= 60;
            operand1.reg &= 1;
            operand2.reg &= 3;
        }

        opcode |= (operand1.val<<20) + (operand2.val<<8) + (operand1.reg<<5) + (operand2.reg<<7) + ( (k1ext&1) << 4);
    }

    //REG,IMR (LSU)
    if(operand1.type == OP_REG && operand2.type == OP_IMR && operand3.type == OP_VOID)
    {
        eval_expr(operand2.value,&val,sec,pc);
        operand2.val = val&0xFFFF;

        type = (opcode>>2)&0x3;

        if(inst == 1) //LSU
        {
        	if(type == 0) //LDM/STM
	        {
	            operand2.val &= 0x7FFF;
	            opcode |= (plus<<5) + ( (k1ext&3)<<6);
	            opcode |= (operand1.reg<<26) + (operand2.reg<<20) + (operand2.val<<8);
	        }else
	        {
	
                if(type == 1)//LDC/STC
                {
                    operand2.val &= 0x7FFF;
                    opcode |= (plus<<4) + ( (k1ext&3)<<6);
                    opcode |= (operand1.reg<<26) + (operand2.reg<<20) + (operand2.val<<8);
                }else //LDMV/STMV ,LDCV/STCV
                {
                	operand2.val &= 0x1FFF;
                    opcode |= (plus<<6) + ( (k1ext&3)<<8);
                    opcode |= (operand1.reg<<26) + (operand2.reg<<20) + (operand2.val<<10);

                }
	            
	        }

        }
    }


    //REG,RLR (Move LRL)
    if(operand1.type == OP_REG && operand2.type == OP_RLR && operand3.type == OP_VOID)
    {
        opcode |= (operand1.reg<<26);
    }

    //RLR,REG (Move SRL)
    if(operand1.type == OP_RLR && operand2.type == OP_REG && operand3.type == OP_VOID)
    {
        opcode |= (operand1.reg<<26);
    }

    //BLR,REG (Move SRL)
    if(operand1.type == OP_RBR && operand2.type == OP_REG && operand3.type == OP_VOID)
    {
        opcode |= (operand1.reg<<26);
    }

    //REG,REG (CMP/MOVE)
    if(operand1.type == OP_REG && operand2.type == OP_REG && operand3.type == OP_VOID)
    {
        if(inst == 2)
    	   opcode |= (operand1.reg<<26) + (operand2.reg<<20) + ( (k1ext&3)<<6);
        else
            opcode |= (operand1.reg<<26) + (operand2.reg<<20) + ( (k1ext&3)<<8);
    }


    //REG,REG,REG (ALU)
    if(operand1.type == OP_REG && operand2.type == OP_REG && operand3.type == OP_REG)
    {
        opcode |= (operand1.reg<<26) + (operand2.reg<<20) + (operand3.reg<<14) + ( (k1ext&3)<<12);
    }

    //REG,REG,IMM (ALU)
    if(operand1.type == OP_REG && operand2.type == OP_REG && operand3.type == OP_IMM)
    {
    	eval_expr(operand3.value,&val,sec,pc);
        operand3.val = val&0xFFFF;

        if(inst == 2)
        {
            /*
        	type = (opcode>>2)&0xF;
	        if(type > 9)
	        	operand3.val = val&0x3F;
            */

            operand3.val = val&0x3FF;

	        opcode |= (operand1.reg<<26) + (operand2.reg<<20) + (operand3.val<<10) + ( (k1ext&3)<<8);
        }else
        {
        	if(inst == 0)
        	{
        		type = (opcode>>4)&0xF;

        		operand3.val = val&0xFFF;
        	    opcode |= (operand1.reg<<26) + (operand2.reg<<20) + (operand3.val<<8);

        	}
        }
        
    }

    //IMM,REG (IN/OUT)
    if(operand1.type == OP_IMM && operand2.type == OP_REG && operand3.type == OP_VOID)
    {
        eval_expr(operand1.value,&val,sec,pc);

        //type = (opcode>>2)&0x3;
        //printf("ok %d\n",type);
        if(inst == 1)
        {
            operand1.val = val&0xFF;
            opcode |= ( (k1ext&3)<<8);
            opcode |= (operand1.val<<18) + (operand2.reg<<26);

        }

    }

    //IMM,IMM 
    if(operand1.type == OP_IMM && operand2.type == OP_IMM && operand3.type == OP_VOID)
    {
    	if(inst == 1) //(OUTI)
    	{
    		eval_expr(operand1.value,&val,sec,pc);
	        operand1.val = val&0xFF;

	        eval_expr(operand2.value,&val,sec,pc);
	        operand2.val = val&0xFFFF;

	        opcode |= ( (k1ext&1)<<4);
	        opcode |= (operand1.val<<24) + (operand2.val<<8);
    	}
    }

    //REG,IMM
    if(operand1.type == OP_REG && operand2.type == OP_IMM && operand3.type == OP_VOID)
    {
        eval_expr(operand2.value,&val,sec,pc);
        if(inst == 2) //ALU
        {
            type = (opcode>>2)&0x3;
            if(type == 2)
            {
                operand2.val = val&0xFFFF;
                /*
                type = (opcode>>2)&0xF;
                if(type > 9)
        			operand2.val = val&0x3F;*/
                
        		opcode |= (operand1.reg<<26) + (operand2.val<<10) + ( (k1ext&3)<<8);
            }else
            {
            	if(type == 3) //movei
            	{
        			operand2.val = val&0xFFFFF;
                	opcode |= (operand1.reg<<26) + (operand2.val<<6)+ ( (k1ext&3)<<4);
            	}
                
            } 
        }

        type = (opcode>>2)&0x3;

        if(inst == 1) //LSU
        {
        	if(type == 0) //LDM/STM
	        {
	            operand2.val &= 0x7FFF;
	            opcode |= ( (k1ext&3)<<6);
	            opcode |= (operand1.reg<<26) + (operand2.reg<<20) + (operand2.val<<8);
	        }else
	        {
	
                if(type == 1)//LDC/STC
                {
                    operand2.val &= 0x7FFF;
                    opcode |= ( (k1ext&3)<<6);
                    opcode |= (operand1.reg<<26) + (operand2.reg<<20) + (operand2.val<<8);
                }else //LDMV/STMV ,LDCV/STCV
                {
                	operand2.val &= 0x1FFF;
                    opcode |= ( (k1ext&3)<<8);
                    opcode |= (operand1.reg<<26) + (operand2.reg<<20) + (operand2.val<<10);

                }
	            
	        }

        }

        if(inst == 0) //CMP
        {
            //cmpi
            operand2.val = val&0xFFFFF;
            opcode |= (operand1.reg<<26) + (operand2.val<<6)+ ( (k1ext&3)<<4);

        }
    }

    //--------------------------------------------------------------
    //VP,IMM
    if(operand1.type == OP_VP && operand2.type == OP_IMM && operand3.type == OP_VOID)
    {
        float fval;
        eval_expr(operand2.value,&val,sec,pc);

        
        //printf("%f\n",operand2.fval);
        if(inst == 0) //VF
        {
            
        }

        if(inst == 3) //BRU
        {
        	//printf("%d\n",val);
            operand2.val = val&0xFFFF;
            opcode |= (operand1.val<<25) + (operand2.val<<9) + (k1ext&3);

        }
    }

    //VP,IMR
    if(operand1.type == OP_VP && operand2.type == OP_IMR && operand3.type == OP_VOID)
    {
        eval_expr(operand2.value,&val,sec,pc);
        operand2.val = val&0xFFFF;

        type = (opcode>>2)&0xF;

        if(type == 0)
        {
            //operand2.reg -= 58;
            //operand2.reg &= 1;

            opcode |= (operand1.val<<8) + (operand2.reg<<15) + (operand2.val<<16) + (k1ext&3);
        }else
        {
            operand2.val = val&0x7FF;
            opcode |= (operand1.val<<25) + (operand2.reg<<19) + (operand2.val<<8) + (k1ext&3) + (plus<<7);
        }
    }


    //VP,VP,VP
    if(operand1.type == OP_VP && operand2.type == OP_VP && operand3.type == OP_VP)
    {
        opcode |= (operand1.val<<25) + (operand2.val<<19) + (k1ext&3);
    }

    //VP,VP
    if(operand1.type == OP_VP && operand2.type == OP_VP && operand3.type == OP_VOID)
    {
    	if(inst == 0)
        {
        	int tmp = 1<<4;
        	if(k1ext == 1)
            	tmp = 1<<5;
            
            opcode |= (operand1.reg<<26) + (operand2.reg<<20) + tmp;
        }
        else
        {

        }
        
    }
    //--------------------------------------------------------------
    //REG
    if(operand1.type == OP_REG && operand2.type == OP_VOID && operand3.type == OP_VOID)
    {
        opcode |= (operand1.val<<26);
    }

    //IMM
    if(operand1.type == OP_IMM && operand2.type == OP_VOID && operand3.type == OP_VOID)
    {
        eval_expr(operand1.value,&val,sec,pc);


        if(inst == 0) //Delay instruction
        {
        	type = (opcode>>6)&3;
	        if(type == 0) //Bcc
	        {
	        	val = (val-pc-4-1)>>3;
	        	val++;
		        operand1.val = val&0x3FFF;
		        //printf("%d %x\n",operand1.val,operand1.val);
		        //printf("%d %x\n",val,val);
		        //printf("%d\n",val);
		        opcode |= (operand1.val<<18);
	        }else 
	        {
	        	type = (opcode>>8)&7;
	        	if(type == 6) //swt
	        	{
	        		operand1.val = val&0x1;
		        	opcode |= (operand1.val<<8);
	        	}else //jump/call
	        	{
                    //printf("%d\n",val);
                    if(val == 0)
                    {
                        operand1.val = 0;
                    }else
                    {
                        val = (val-4-1)>>3;
                        val++;
                        operand1.val = val&0x3FFF;
                    }

                    //printf("%d\n",val);
                    
                    //printf("%d\n",operand1.val);
		        	opcode |= (operand1.val<<18);
	        	}
	        }
        }
    } 
/*
    //REG,REG,IMM
    if(operand1.type == OP_REG && operand2.type == OP_REG && operand3.type == OP_IMM)
    {
        eval_expr(operand3.value,&val,sec,pc);

        type = (opcode>>4)&0x01;

        operand3.val = val&0xFFFF;
        opcode |= (operand1.val<<26) + (operand2.val<<5) + (k1ext&3);
    }
*/

//printf("%d\n",k1ext&3);





    //printf("%s\n",outbin(opcode));
    //printbin(opcode);
    

    val = opcode;
    db->size = 4;
    

	d = db->data = mymalloc(db->size);
	*d++ = (val)&0xFF;
	*d++ = (val>>8)&0xFF;
	*d++ = (val>>16)&0xFF;
    *d++ = (val>>24)&0xFF;


    return db;
}

/* Create a dblock (with relocs, if necessary) for size bits of data. */
dblock *eval_data(operand *op,taddr bitsize,section *sec,taddr pc)
{
    dblock *db=new_dblock();
    unsigned char *d;
    operand operand1;
    int val;

    operand1 = op[0];

    eval_expr(operand1.value,&val,sec,pc);

    db->size = 4;
    d = db->data = mymalloc(db->size);

    

    *d++ = (val)&0xFF;
	*d++ = (val>>8)&0xFF;
	*d++ = (val>>16)&0xFF;
	*d++ = (val>>24)&0xFF;
    

    return db;
}



/* Calculate the size of the current instruction; must be identical
   to the data created by eval_instruction. */
taddr instruction_size(instruction *p,section *sec,taddr pc)
{
    //printf("ok\n",len);
    return 1;
}

operand *new_operand()
{
    operand *new = mymalloc(sizeof(*new));
    new->type = -1;
    return new;
}


/* return true, if initialization was successfull */
int init_cpu()
{
    return 1;
}

/* return true, if the passed argument is understood */
int cpu_args(char *p)
{

    /* no args */
    return 0;
}
/* parse cpu-specific directives; return pointer to end of
   cpu-specific text */
char *parse_cpu_special(char *start)
{
    //printf("ok\n",len);
    /* no specials */
    return start;
}

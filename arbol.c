#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Arbol SPL
typedef struct Estud{
    int dato;
    char info[50];
    int busqueda;
    struct Estud *derecha;
    struct Estud *izquierda;
}estudiante;

estudiante *cabeza;

//Variables
FILE *f;

//Declaracion de metodos
void Insertar(int dato, char info[]);
void Graficar(estudiante *Nodo);
void Mostrar();
void Modificar(int dato, char info[]);
estudiante *Buscar(estudiante *root, int key);
estudiante *splay(estudiante *root, int key);
estudiante *RotacionIzquierda(estudiante *x);
estudiante *RotacionDerecha(estudiante *x);
//------------------------------------------------------------------------------
int main(){
	int opcion = 0;
	int num;
	char info[50];
	while(opcion!=6){
		printf("1. Insertar\n");
		printf("2. Modificar\n");
		printf("3. Eliminar\n");
		printf("4. Buscar\n");
		printf("5. Mostrar\n");
		printf("6. Salir\n");
		scanf("%d", &opcion);
		printf("\n\n\n");
		switch(opcion){
			case 1:
				/*printf("Ingrese un numero:\n");
				scanf("%d",&num);
				printf("Ingrese un texto:\n");
				scanf("%s",info);
				Insertar(num, info);*/
				Insertar(7,"siete");
				Insertar(5,"cinco");
				Insertar(3,"tres");
				Insertar(4,"cuatro");
				Insertar(9,"nueve");
				Insertar(12,"doce");
				Insertar(10,"diez");
				Insertar(1,"uno");
				Insertar(15,"quince");
				Insertar(6,"seis");
				Insertar(20,"veinte");
				Insertar(14,"catorce");
				Insertar(2,"dos");
				Insertar(8,"ocho");
				printf("\n\n\n");
			break;

			case 2:
				printf("Ingrese un numero a modificar:\n");
				scanf("%d",&num);
				printf("Ingrese nuevo texto:\n");
				scanf("%s",info);
				Modificar(num, info);
				printf("\n\n\n");
			break;

			case 3:

			break;

			case 4:
				printf("Ingrese el numero que desea buscar:\n");
				scanf("%d", &num);
				cabeza = Buscar(cabeza, num);
				printf("id: %i\n", cabeza->dato);
				printf("id: %s\n", cabeza->info);
				printf("\n\n\n");
			break;

			case 5:
				Mostrar();
				printf("\n\n\n");
			break;
		}
	}
	return 0;
}

void Insertar(int dato, char info[]){
	estudiante *nuevo = (estudiante*)malloc(sizeof(estudiante));
    nuevo->dato = dato;
    strcpy(nuevo->info,info);
    if(!cabeza){
    	cabeza = nuevo;
    }
    else{
    	estudiante *actual = cabeza, *aux = cabeza;
    	while(actual){
    		if(actual->dato < dato){
    			aux = actual;
    			actual = actual->derecha;
    		}
    		else if(actual->dato == dato){
    			printf("ya existe\n");
    			break;
    		}
    		else{
    			aux = actual;
    			actual = actual->izquierda;
    		}
    	}
    	if(aux->dato < dato){
    		actual = nuevo;
    		aux->derecha = actual;
    	}
    	else if(aux->dato > dato){
    		actual = nuevo;
    		aux->izquierda = actual;
    	}
    }
}

/*estudiante * Insertar(estudiante *node, int dato, char info[]){
    if(!node){
        node = (estudiante*)malloc(sizeof (estudiante));
        node->dato = dato;
        strcpy(node->info,info);
    }
    else if(node->dato > dato){
        node->izquierda = Insertar(node->izquierda,dato,info);
    }
    else if(node->dato < dato){
        node->derecha = Insertar(node->derecha,dato,info);
    }
    return node;
}*/

void Modificar(int dato, char info[]){
	estudiante *aux = cabeza;
	char estado = 'a';
    while (aux) {
        if(aux->dato<dato){
            aux = aux->derecha;
        }
        else if(aux->dato==dato){
        	estado = 's';
        	printf("Valor actual: %s\n", aux->info);
        	printf("Valor nuevo: %s\n", info);
            strcpy(aux->info, info);
            break;
        }
        else{
            aux = aux->izquierda;
        }
    }
    if(estado=='a'){
    	printf("No se encontró el nodo\n");
    }
}

void Mostrar(){
    char direccion[] = "/home/andres/Escritorio/201503797/Arbol.dot";
    f = fopen(direccion,"w");
    if(!f){
        printf("nel\n");
    }
    else{
        fprintf (f, "digraph G {\n");
        //archivo << "digraph G {" << endl;
        fprintf (f, "node[shape = oval];\n");
        //archivo << "node[shape = oval];" << endl;
        estudiante *arb = cabeza;
        Graficar(arb);
        fprintf (f, "}");
        //archivo << "}" << endl;
        fclose(f);
        system("dot -Tpng /home/andres/Escritorio/201503797/Arbol.dot -o /home/andres/Escritorio/201503797/Arbol.png");
        system("nohup display /home/andres/Escritorio/201503797/Arbol.png &");
    }
}

void Graficar(estudiante *Nodo){
    if(Nodo)
    {
    	fprintf (f, "Nodo%p [label = \"%i\"];\n",&*Nodo,Nodo->dato);
        //archivo << "Nodo" << &*Nodo <<" [label=\"" << Nodo->carnet << "\"];\n" << endl;

        if(Nodo->izquierda){
        	fprintf (f, "Nodo%p-> Nodo%p;\n",&*Nodo,&*Nodo->izquierda);
            //archivo << "Nodo" << &*Nodo << "-> Nodo" << &*Nodo->izquierda << ";\n";
            Graficar(Nodo->izquierda);
        }
        if(Nodo->derecha){
        	fprintf (f, "Nodo%p-> Nodo%p;\n",&*Nodo,&*Nodo->derecha);
            //archivo << "Nodo" << &*Nodo << "-> Nodo" << &*Nodo->derecha << ";\n";
            Graficar(Nodo->derecha);
        }
    }
}

estudiante *RotacionDerecha(estudiante *x) 
{ 
    estudiante *y = x->izquierda; 
    x->izquierda = y->derecha; 
    y->derecha = x; 
    return y; 
} 
  
// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
estudiante *RotacionIzquierda(estudiante *x) 
{ 
    estudiante *y = x->derecha; 
    x->derecha = y->izquierda; 
    y->izquierda = x; 
    return y; 
} 

estudiante *splay(estudiante *raiz, int dato) 
{ 
    if (raiz == NULL || raiz->dato == dato) 
        return raiz; 
    if (raiz->dato > dato) 
    { 
        if (raiz->izquierda == NULL) return raiz; 

        if (raiz->izquierda->dato > dato) 
        { 
            raiz->izquierda->izquierda = splay(raiz->izquierda->izquierda, dato); 
            raiz = RotacionDerecha(raiz); 
        } 
        else if (raiz->izquierda->dato < dato)
        { 
            raiz->izquierda->derecha = splay(raiz->izquierda->derecha, dato); 
            if (raiz->izquierda->derecha != NULL) 
                raiz->izquierda = RotacionIzquierda(raiz->izquierda); 
        } 
        return (raiz->izquierda == NULL)? raiz: RotacionDerecha(raiz); 
    } 
    else
    { 
        if (raiz->derecha == NULL) return raiz; 

        if (raiz->derecha->dato > dato) 
        { 
            raiz->derecha->izquierda = splay(raiz->derecha->izquierda, dato); 

            if (raiz->derecha->izquierda != NULL) 
                raiz->derecha = RotacionDerecha(raiz->derecha); 
        } 
        else if (raiz->derecha->dato < dato)
        { 
            raiz->derecha->derecha = splay(raiz->derecha->derecha, dato); 
            raiz = RotacionIzquierda(raiz); 
        } 
        return (raiz->derecha == NULL)? raiz: RotacionIzquierda(raiz); 
    } 
} 
estudiante *Buscar(estudiante *raiz, int dato) 
{ 
    return splay(raiz, dato); 
} 


#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct plant {
    char name;
    int ID;
	int age;
	int maxAge;
	float shade;
	float maxShade;
	float height;
	float maxHeight;
	float width;
	int minTemp;
	int maxTemp;
	float growthRate;
	int seedAge;
	int ageTillSeed;
	int seedAmount;
    int seedRadius;
    int isSeed;
    int isAlive;

};

struct plant newPlant(char nname, int nID, int nmaxAge, float nmaxShade, float nheight, int nminTemp, int nmaxTemp, float ngrowthRate, int nseedAge, int nseedAmount, int nseedRadius) {
	struct plant newp;
    newp.name = nname;
    newp.ID = nID;
	newp.age = 0;
	newp.maxAge = nmaxAge;
	newp.shade = 0.0;
	newp.maxShade = nmaxShade;
	newp.height = 0;
	newp.maxHeight = nheight;
	newp.width = newp.height / 3;
	newp.minTemp = nminTemp;
	newp.maxTemp = nmaxTemp;
	newp.growthRate = ngrowthRate;
	newp.seedAge = nseedAge;
	newp.ageTillSeed = 0;
	newp.seedAmount = nseedAmount;
    newp.seedRadius = nseedRadius;
    newp.isSeed = 0;
    newp.isAlive = 0;
    return newp;
}

struct Node {
	struct plant data;
	struct Node* next;
};

struct Node* newNode(struct plant p) {
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = p;
	temp->next = NULL;
	return temp;
};

struct Queue {
	struct Node* front, * rear;
};

struct Queue* createQueue() {
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->front = NULL;
	q->rear = NULL;
	return q;
};

void enQueue(struct Queue* q, struct plant p) {
	struct Node* temp = newNode(p);
	if (q->rear == NULL) {
		q->front = q->rear = temp;
		return;
	}

	q->rear->next = temp;
	q->rear = temp;
}

struct Queue* createNewQueue(char dir[256]) {
    struct Queue* newQueue = createQueue();

    FILE* fp = fopen(dir, "r");        //read file
    if (!fp)
        printf("Can't open file");          //error case
    else {
        char buffer[1024];
        int row = 0;
        int col = 0;

        while (fgets(buffer, 1024, fp)) {
            col = 0;
            row++;

            if (row == 1)
                continue;

            char* val = strtok(buffer, ",");
            char name;
            int ID;
            int maxAge = 0;
            float maxShade = 0;
            float height = 0;
            int minTemp = 0;
            int maxTemp = 0;
            float growthRate = 0;
            int seedAge = 0;
            int seedAmount = 0;
            int seedRadius = 0;
            while (val) {
                int floatVal = atof(val);
                int intVal = atoi(val);
                if (col == 0) {
                    name = val;
                }
                if (col == 1) {
                    ID = intVal;
                }
                if (col == 2) {
                    maxAge = floatVal;
                }
                if (col == 3) {
                    maxShade = floatVal;
                }
                if (col == 4) {
                    height = intVal;
                }
                if (col == 5) {
                    minTemp = intVal;
                }
                if (col == 6) {
                    maxTemp = intVal;
                }
                if (col == 7) {
                    growthRate = floatVal;
                }
                if (col == 8) {
                    seedAge= intVal;
                }
                if (col == 9) {
                    seedAmount = intVal;
                }
                if (col == 10) {
                    seedRadius = intVal;
                }
                val = strtok(NULL, ", ");
                col++;
            }
            enQueue(newQueue, newPlant(name, ID, maxAge, maxShade, height, minTemp, maxTemp, growthRate, seedAge, seedAmount, seedRadius));
        }
        fclose(fp);
    }
    return newQueue;
}

int main() {

    char path[256];
    printf("Path:");
    gets(path);
    struct Queue* plantQueue = createNewQueue(path);
    struct Node* current = plantQueue->front;

    struct plant grid[100][100];
    int i, j;
    for (i = 0; i < 100; i += 3) {
        for (j = 0; j < 100; j += 3) {
            grid[i][j] = current->data;
            grid[i][j].isAlive = 1;
            current = current->next;
            if (current == NULL) {
                current = plantQueue->front;
            }
        }
    }

    for (i = 0; i < 100; i += 3) {
        for (j = 0; j < 100; j += 3) {
            struct plant currPlant = grid[i][j];
            //printf("%d\t", currPlant.ID);
            if (j == 99) {
                //printf("\n");
            }
        }
    }

    int year = 0;
    while (year < 400) {
        for (i = 0; i < 100; i += 1) {
            for (j = 0; j < 100; j += 1) {
                struct plant currPlant = grid[i][j];
                if (currPlant.isAlive == 1) {
                    if (currPlant.maxAge == currPlant.age) {
                        currPlant.isAlive = 0;
                    }
                    if ((currPlant.height < currPlant.maxHeight) && (currPlant.isAlive == 1)) {
                        currPlant.height += currPlant.growthRate;
                        currPlant.width = currPlant.height / 3;
                    }
                    if (currPlant.ageTillSeed == currPlant.seedAge) {
                        for (int i = 0; i <= currPlant.seedAmount; i++) {
                            int x = rand() % (currPlant.seedRadius + 1);
                            int y = rand() % (currPlant.seedRadius + 1);

                            if ((i - x) <= 0) {
                                if ((j - y) <= 0) {
                                    if (grid[0][0].isAlive != 1 && grid[0][0].isSeed != 1) {
                                        grid[0][0] = currPlant;
                                        grid[0][0].isSeed = 1;
                                        grid[0][0].isAlive = 0;
                                    }
                                    if (grid[0][0].isAlive != 1 && grid[0][0].isSeed == 1) {
                                        if (grid[0][0].growthRate < currPlant.growthRate) {
                                            grid[0][0] = currPlant;
                                            grid[0][0].isSeed = 1;
                                            grid[0][0].isAlive = 0;
                                        }
                                    }
                                }
                                if ((j + y) > 100) {
                                    if (grid[0][99].isAlive != 1 && grid[0][99].isSeed != 1) {
                                        grid[0][99] = currPlant;
                                        grid[0][99].isSeed = 1;
                                        grid[0][99].isAlive = 0;
                                    }
                                    if (grid[0][99].isAlive != 1 && grid[0][99].isSeed == 1) {
                                        if (grid[0][99].growthRate < currPlant.growthRate) {
                                            grid[0][99] = currPlant;
                                            grid[0][99].isSeed = 1;
                                            grid[0][99].isAlive = 0;
                                        }
                                    }
                                }
                                else {
                                    if (grid[0][y].isAlive != 1 && grid[0][y].isSeed != 1) {
                                        grid[0][y] = currPlant;
                                        grid[0][y].isSeed = 1;
                                        grid[0][y].isAlive = 0;
                                    }
                                    if (grid[0][y].isAlive != 1 && grid[0][y].isSeed == 1) {
                                        if (grid[0][y].growthRate < currPlant.growthRate) {
                                            grid[0][y] = currPlant;
                                            grid[0][y].isSeed = 1;
                                            grid[0][y].isAlive = 0;
                                        }
                                    }
                                }
                            }
                            if ((i + x) > 100) {
                                if ((j - y) <= 0) {
                                    if (grid[99][0].isAlive != 1 && grid[99][0].isSeed != 1) {
                                        grid[99][0] = currPlant;
                                        grid[99][0].isSeed = 1;
                                        grid[99][0].isAlive = 0;
                                    }
                                    if (grid[99][0].isAlive != 1 && grid[99][0].isSeed == 1) {
                                        if (grid[99][0].growthRate < currPlant.growthRate) {
                                            grid[99][0] = currPlant;
                                            grid[99][0].isSeed = 1;
                                            grid[99][0].isAlive = 0;
                                        }
                                    }
                                }
                                if ((j + y) > 100) {
                                    if (grid[99][99].isAlive != 1 && grid[99][99].isSeed != 1) {
                                        grid[99][99] = currPlant;
                                        grid[99][99].isSeed = 1;
                                        grid[99][99].isAlive = 0;
                                    }
                                    if (grid[99][99].isAlive != 1 && grid[99][99].isSeed == 1) {
                                        if (grid[99][99].growthRate < currPlant.growthRate) {
                                            grid[99][99] = currPlant;
                                            grid[99][99].isSeed = 1;
                                            grid[99][99].isAlive = 0;
                                        }
                                    }
                                }
                                else {
                                    if (grid[99][y].isAlive != 1 && grid[99][y].isSeed != 1) {
                                        grid[99][y] = currPlant;
                                        grid[99][y].isSeed = 1;
                                        grid[99][y].isAlive = 0;
                                    }
                                    if (grid[99][y].isAlive != 1 && grid[99][y].isSeed == 1) {
                                        if (grid[99][y].growthRate < currPlant.growthRate) {
                                            grid[99][y] = currPlant;
                                            grid[99][y].isSeed = 1;
                                            grid[99][y].isAlive = 0;
                                        }
                                    }
                                }
                            }
                            if ((j - y) <= 0) {
                                grid[x][0];
                                if (grid[x][0].isAlive != 1 && grid[x][0].isSeed != 1) {
                                    grid[x][0] = currPlant;
                                    grid[x][0].isSeed = 1;
                                    grid[x][0].isAlive = 0;
                                }
                                if (grid[x][0].isAlive != 1 && grid[x][0].isSeed == 1) {
                                    if (grid[x][0].growthRate < currPlant.growthRate) {
                                        grid[x][0] = currPlant;
                                        grid[x][0].isSeed = 1;
                                        grid[x][0].isAlive = 0;
                                    }
                                }
                            }
                            if ((j + y) > 100) {
                                if (grid[x][99].isAlive != 1 && grid[x][99].isSeed != 1) {
                                    grid[x][99] = currPlant;
                                    grid[x][99].isSeed = 1;
                                    grid[x][99].isAlive = 0;
                                }
                                if (grid[x][99].isAlive != 1 && grid[x][99].isSeed == 1) {
                                    if (grid[x][99].growthRate < currPlant.growthRate) {
                                        grid[x][99] = currPlant;
                                        grid[x][99].isSeed = 1;
                                        grid[x][99].isAlive = 0;
                                    }
                                }
                            }
                            if (grid[x][y].isAlive != 1 && grid[x][y].isSeed != 1) {
                                grid[x][y] = currPlant;
                                grid[x][y].isSeed = 1;
                                grid[x][y].isAlive = 0;
                            }
                            if (grid[x][y].isAlive != 1 && grid[x][y].isSeed == 1) {
                                if (grid[x][y].growthRate < currPlant.growthRate) {
                                    grid[x][y] = currPlant;
                                    grid[x][y].isSeed = 1;
                                    grid[x][y].isAlive = 0;
                                }
                            }
                        }
                    }
                    currPlant.age++;
                    currPlant.ageTillSeed++;
                    //printf("%d, %d\t", i, j);
                }
            }
        }
        for (i = 0; i < 100; i += 1) {
            for (j = 0; j < 100; j += 1) {
                if (grid[i][j].isSeed == 1) {
                    grid[i][j].isSeed = 0;
                    grid[i][j].isAlive = 1;
                    //printf("seed Grow");
                }
            }

        }
        year++;

    }
    FILE* outFile = fopen("output1.csv", "w");
    fprintf(outFile, "X, Y, Type\n");
    printf("\n\n\n\n\n");
    for (i = 0; i < 100; i += 1) {
        for (j = 0; j < 100; j += 1) {
            struct plant currPlant = grid[i][j];
            if (currPlant.isAlive == 1 || currPlant.isSeed == 1) {
                printf("(%d, %d) %d\t", i, j, currPlant.ID);
                fprintf(outFile, "%d, %d, %d\n", i, j, currPlant.ID);
                if (j == 99) {
                    printf("\n");
                }
            }
            
        }
    }
}

    
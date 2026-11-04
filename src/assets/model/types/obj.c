#include "assets/model/types/obj.h"

#include <SDL3/SDL_iostream.h>
#include "shared_types.h"

#define PAIR(c1, c2) (((c1) << 8) | (c2))

int OBJ_Parse(char *filepath, Model *model)
{
    if (!filepath)
    {
        printf("Can't parse a NULL filepath");
        return ERROR;
    }
    if (!model)
    {
        printf("Can't use a NULL model");
        return ERROR;
    }

    size_t file_size;

    char *file_data = SDL_LoadFile(filepath, &file_size);
    char *line_data;
    char *token_data;
    char *tri_data;
    char* line = SDL_strtok_r(file_data, "\n", &line_data);
    char* token;
    char* triToken;

    uint16_t hash;

    Vector3 *temp3;
    Vector2 *temp2;
    Tri *tempTri;

    while (line) {
        //printf("line: %s\n", line);

        token = SDL_strtok_r(line, " ", &token_data);
        if (token)
        {
            hash = PAIR(token[0], token[1]);
            token = SDL_strtok_r(NULL, " ", &token_data);
            //printf("Current token %s\n", token);
            switch (hash)
            {
                case PAIR('v', '\0'):
                    temp3 = SDL_malloc(sizeof(Vector3));
                    for (int i = 0; i < 3; i++)
                    {
                        //printf("vertex token: %s\n", token);
                        (*temp3)[i] = (float)SDL_atof(token);
                        token = SDL_strtok_r(NULL, " ", &token_data);
                    }
                    List_Append(model->positions, temp3);
                    break;
                
                case PAIR('v', 't'):
                    temp2 = SDL_malloc(sizeof(Vector2));
                    for (int i = 0; i < 2; i++)
                    {
                        (*temp2)[i] = (float)SDL_atof(token);
                        token = SDL_strtok_r(NULL, " ", &token_data);
                    }
                    List_Append(model->texels, temp2);
                    break;

                case PAIR('v', 'n'):
                    temp3 = SDL_malloc(sizeof(Vector3));
                    for (int i = 0; i < 3; i++)
                    {
                        (*temp3)[i] = (float)SDL_atof(token);
                        token = SDL_strtok_r(NULL, " ", &token_data);
                    }
                    List_Append(model->normals, temp3);
                    break;
                    
                case PAIR('f', '\0'):

                    tempTri = SDL_malloc(sizeof(Tri));

                    triToken = SDL_strtok_r(token, "/", &tri_data);
                    for (int i = 0; i < 9; i++)
                    {
                        if (i % 3 == 0 && i != 0)
                        {
                            token = SDL_strtok_r(NULL, " ", &token_data);
                            //printf("advanced token to %s\n", token);
                            triToken = SDL_strtok_r(token, "/", &tri_data);
                        }
                        //printf("Current face token %i %s\n", i, triToken);
                        (*tempTri)[i] = -1 + (int)SDL_atoi(triToken);
                        triToken = SDL_strtok_r(NULL, "/", &tri_data);
                    }
                    List_Append(model->tris, tempTri);
                    break;

                case PAIR('#', '0'):
                    line = SDL_strtok_r(NULL, "\n", &line_data);
                    continue;

                default:
                    line = SDL_strtok_r(NULL, "\n", &line_data);
                    continue;
            }
        }

        line = SDL_strtok_r(NULL, "\n", &line_data);
    }
    printf("Finished Parsing %s\n", filepath);
    return SUCCESS;
}
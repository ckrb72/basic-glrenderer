#include <graphics.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "./core/Shader.h"
#include "./core/Window.h"
#include "./math/lnal.h"

int main()
{
    Window win("Spooky Game!!!!!", 1280, 720);
    glEnable(GL_DEPTH_TEST);

    Shader s;
    if(!s.load("./test.vert", "./test.frag"))
    {
        std::cout << "Failed to load shader" << std::endl;
    }

    float vertices[] = 
    {
        -0.5, -0.5, -1.0,
        0.5, -0.5, -1.0,
        0.5, 0.5, -1.0,
        -0.5, 0.5, -1.0
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    uint32_t vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    lnal::mat4 projection;
    lnal::gen_perspective_proj(projection, PI / 2, (float)(1280.0f/720.0f), 0.1, 10.0);

    s.set_mat4fv("projection", projection.data());

    bool quit = false;

    while(!quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.3, 0.3, 0.3, 1.0);

        s.bind();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        win.swap_buffers();
    }

    return 0;
}
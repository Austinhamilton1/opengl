#include "Generate.h"

//create a plane with width and height
std::shared_ptr<gl::VertexBuffer> gl::Generate::plane(float width, float height, glm::vec3 color, glm::vec2 tex) {
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    //vertex buffer
    std::shared_ptr<gl::VertexBuffer> plane = std::make_shared<gl::VertexBuffer>(gl::STATIC);

    //add the vertex data
    plane->addData(8, 32,
        halfWidth, halfHeight, 0.0f, color.r, color.g, color.b, tex.s, tex.t, //top right
        halfWidth, -halfHeight, 0.0f, color.r, color.g, color.b, tex.s, 0.0f, //bottom right
        -halfWidth, -halfHeight, 0.0f, color.r, color.g, color.b, 0.0f, 0.0f, //bottom left
        -halfWidth, halfHeight, 0.0f, color.r, color.g, color.b, 0.0f, tex.t //top left
    );

    //set attributes
    plane->setLayout(0, 3, 8 * sizeof(float), 0);
    plane->setLayout(1, 3, 8 * sizeof(float), 3 * sizeof(float));
    plane->setLayout(2, 2, 8 * sizeof(float), 6 * sizeof(float));

    //index buffer
    std::shared_ptr<gl::IndexBuffer> indexes = std::make_shared<gl::IndexBuffer>(gl::STATIC);

    //add the index data
    indexes->addData(6,
        0, 1, 3,
        1, 2, 3
    );

    //set the index buffer
    plane->setIndexBuffer(indexes);

    return plane;
}

//create a cube width width, height, and depth
std::shared_ptr<gl::VertexBuffer> gl::Generate::cube(float width, float height, float depth, glm::vec3 color, glm::vec2 tex) {
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float halfDepth = depth / 2.0f;

    //vertex buffer
    std::shared_ptr<gl::VertexBuffer> cube = std::make_shared<gl::VertexBuffer>(gl::STATIC);

    //add the vertex data
    cube->addData(8, 192,
        //front face
        -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex.t,
        -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f,
        halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f,
        halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, tex.t,
        //right face
        halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, tex.t,
        halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f,
        halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, 0.0f,
        halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, tex.t,
        //back face
	    halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t,
        halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, 0.0f,
        -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, 0.0f,
        -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, tex.t,
        //left face
	    -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t,
        -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, 0.0f,
        -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f,
        -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, tex.t,
        //top face
        -halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t,
        -halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f,
        halfWidth, halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f,
        halfWidth, halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, tex.t,
        //bottom face
        halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, 0.0f, tex.t,
        halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, 0.0f, 0.0f,
        -halfWidth, -halfHeight, halfDepth, color.r, color.g, color.b, tex.s, 0.0f,
        -halfWidth, -halfHeight, -halfDepth, color.r, color.g, color.b, tex.s, tex.t
    );

    //set the vertex attributes
    cube->setLayout(0, 3, 8 * sizeof(float), 0);
    cube->setLayout(1, 3, 8 * sizeof(float), 3 * sizeof(float));
    cube->setLayout(2, 2, 8 * sizeof(float), 6 * sizeof(float));

    //index buffer
    std::shared_ptr<gl::IndexBuffer> indexes = std::make_shared<gl::IndexBuffer>(gl::STATIC);

    //add the index data
    indexes->addData(36,
        //front face
        0, 1, 2,
        0, 2, 3,
        //right face
        4, 5, 6,
        4, 6, 7,
        //back face
        8, 9, 10,
        8, 10, 11,
        //left face
        12, 13, 14,
        12, 14, 15,
        //top face
        16, 17, 18,
        16, 18, 19,
        //bottom face
        20, 21, 22,
        20, 22, 23
    );

    //set the index buffer
    cube->setIndexBuffer(indexes);

    return cube;
}
#include "PostProcessor.h"
#include "WindowController.h"
#include "Shader.h"
#include "ToolWindow.h"

PostProcessor::PostProcessor() {

	m_framebuffer = 0;
	m_textureColorbuffer = 0;
	m_renderBufferObject = 0;
	m_postShader = 0;
	m_vertexBuffer = 0;
}

PostProcessor:: ~PostProcessor() { }

void PostProcessor::Cleanup() {
	glDeleteFramebuffers(1, &m_framebuffer);
	glDeleteTextures(1, &m_textureColorbuffer);
	glDeleteRenderbuffers(1, &m_renderBufferObject);
}

void PostProcessor::Create(Shader* _postShader) {
	m_postShader = _postShader;
	CreateBuffers();
	CreateVertices();
}

void PostProcessor::CreateBuffers() {
	
	//Framebuffer configuration
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	//Create a color attachment texture
	glGenTextures(1, &m_textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureColorbuffer);
	Resolution r = WindowController::GetInstance().GetResolution();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.width, r.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorbuffer, 0);

	//Create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, r.width, r.height); //use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject); // now actually attach it

	//Now that we created the framebuffer and added all attachemtns we want to check if it is complete
	M_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::CreateVertices()
{
    // vertex attributes for a quad that fills
    // the entire screen in Normalized Device Coordinates.
    float vertexData[] =
    {
        // positions    // texCoords
        -1.0f,  1.0f,    0.0f, 1.0f,
        -1.0f, -1.0f,    0.0f, 0.0f,
         1.0f, -1.0f,    1.0f, 0.0f,

        -1.0f,  1.0f,    0.0f, 1.0f,
         1.0f, -1.0f,    1.0f, 0.0f,
         1.0f,  1.0f,    1.0f, 1.0f
    };

    // Generate vertex buffer
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

    // Upload vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PostProcessor::BindVertices()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // Bind the vertex buffer

    // 1st attribute buffer = vertices
    glEnableVertexAttribArray(m_postShader->GetAttrVertices());
    glVertexAttribPointer(m_postShader->GetAttrVertices(), // The attribute we want to configure
        2,                               // size (2 components)
        GL_FLOAT,                        // type
        GL_FALSE,                        // normalized?
        4 * sizeof(float),               // stride: 4 floats per vertex definition
        (void*)0                         // array buffer offset
    );

    // 2nd attribute buffer = texCoords
    glEnableVertexAttribArray(m_postShader->GetAttrTexCoords());
    glVertexAttribPointer(m_postShader->GetAttrTexCoords(),   // The attribute we want to configure
        2,                                  // size (2 components)
        GL_FLOAT,                           // type
        GL_FALSE,                           // normalized?
        4 * sizeof(float),                  // stride: 4 floats per vertex definition
        (void*)(2 * sizeof(float))          // array buffer offset
    );
}

void PostProcessor::Start()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void PostProcessor::End()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // Disable depth test so screen-space quad isn't discarded due to depth test.

    glUseProgram(m_postShader->GetProgramID()); // Use our shader
    m_postShader->SetTextureSampler("ScreenTexture", GL_TEXTURE0, 0, m_textureColorbuffer);
    m_postShader->SetInt("BlueTint", OpenGL::ToolWindow::TintBlueEnabled);
    m_postShader->SetInt("WaterScene", OpenGL::ToolWindow::WaterSceneEnabled);
	m_postShader->SetFloat("Time", glfwGetTime());
	m_postShader->SetFloat("Amplitude", OpenGL::ToolWindow::Amplitude);
	m_postShader->SetFloat("Frequency", OpenGL::ToolWindow::Frequency);
	

    BindVertices();

    if(OpenGL::ToolWindow::WireframeEnabled)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
	    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(m_postShader->GetAttrVertices());
    glDisableVertexAttribArray(m_postShader->GetAttrTexCoords());
}

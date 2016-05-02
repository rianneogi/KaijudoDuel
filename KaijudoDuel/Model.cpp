#include "Model.h"

Model::Model() : mMesh(NULL), mTexture(NULL), mShader(NULL), mModelMatrix(1.0f)
{
}

Model::Model(Mesh* mesh, Texture* texture, ShaderProgram* shader) : mMesh(mesh), mTexture(texture), mShader(shader), mModelMatrix(1.0f)
{
}

Model::Model(const Model& other)
{
	mMesh = other.mMesh;
	mTexture = other.mTexture;
	mShader = other.mShader;
	mModelMatrix = other.mModelMatrix;
}

Model::~Model()
{
}

void Model::render()
{
	assert(mMesh != NULL && mTexture != NULL);
	mTexture->bind();
	//mShader->bind();
	//mShader->setWorld(mModelMatrix);
	//mShader->updateWorld();
	/*glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);*/
	mMesh->render();
	/*glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);*/

	GLenum err = GL_NO_ERROR;
	if ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("ERROR: Model render error %d", err);
	}
}

void Model::create(Mesh* mesh, Texture* texture, ShaderProgram* shader)
{
	mMesh = mesh;
	mTexture = texture;
	mShader = shader;
	mModelMatrix = glm::mat4(1.0f);
}

void Model::move(const glm::vec3& vec)
{
	mModelMatrix = glm::translate(mModelMatrix, vec);
}

void Model::setPosition(const glm::vec3& pos)
{
	mModelMatrix = glm::translate(glm::mat4(1.0f), pos);
}

void Model::scale(float value)
{
	mModelMatrix = glm::scale(mModelMatrix, glm::vec3(value, value, value));
}

void Model::setMesh(Mesh* mesh)
{
	mMesh = mesh;
}

void Model::setTexture(Texture* texture)
{
	mTexture = texture;
}

void Model::setShader(ShaderProgram* shader)
{
	mShader = shader;
}

void Model::setModelMatrix(const glm::mat4& mat)
{
	mModelMatrix = mat;
}


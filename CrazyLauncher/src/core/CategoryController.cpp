#include "CategoryController.h"

namespace Cl
{
	CategoryController::CategoryController(QObject* parent /* nullptr */) : QObject(parent) { }
	CategoryController::~CategoryController() {}

	const QList<Category>& CategoryController::GetCategories() const
	{
		return m_categories;
	}

	void CategoryController::AddCategory(const Category& category)
	{
		m_categories.append(category);
		emit E_addCategory(category);
	}

	void CategoryController::RemoveCategory(size_t index)
	{
		m_categories.remove(index);
		emit E_removeCategory(index);
	}

	void CategoryController::EditCategory(size_t index, Category& newCategory)
	{
		Category category = m_categories.at(index);
		category = newCategory;
		emit E_editCategory(index, newCategory);
	}

	void CategoryController::AddProject(const Project& project, int categoryId)
	{
		Category category = m_categories[categoryId];
		category.projects.append(project);
		emit E_addProject(project, categoryId);
	}

	void CategoryController::EditProject(int index, int categoryId, Project& newProject)
	{
		Category category = m_categories[categoryId];

		Project project = category.projects.at(index);
		project = newProject;

		emit E_editProject(index, categoryId);
	}

	void CategoryController::DeleteProject(int index, int categoryId)
	{
		Category category = m_categories[categoryId];
		category.projects.remove(index);
		emit E_deleteProject(index, categoryId);
	}

}
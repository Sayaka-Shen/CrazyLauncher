#pragma once
#include "data/category.h"
#include <QObject>

namespace Cl
{
	class CategoryController : public QObject
	{
		Q_OBJECT

	public:
		explicit CategoryController(QObject* parent = nullptr);
		~CategoryController();

	public:
		const QList<Category>& GetCategories() const;
		void AddCategory(const Category& category);
		void RemoveCategory(size_t index);
		void EditCategory(size_t index, Category& newCategory);

		void AddProject(const Project& project, int categoryId);
		void EditProject(int index, int categoryId, Project& newProject);
		void DeleteProject(int index, int categoryId);

	private:
		QList<Category> m_categories;

	signals:
		void E_addCategory(const Category& category);
		void E_editCategory(size_t index, Category& category);
		void E_removeCategory(size_t index);

		void E_addProject(const Project& project, int categoryId);
		void E_editProject(int index, int categoryId);
		void E_deleteProject(int index, int categoryId);
	};
}
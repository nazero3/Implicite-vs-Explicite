

//THIS CODE HAS THREE PARTS


//THE FIRST PART: METU SPELLING
/*

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkImplicitModeller.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>


int main(int argc, char* argv[])
{
	
	vtkNew<vtkNamedColors> colors;

	// Create lines which spell the word "hello".
	vtkNew<vtkPolyDataReader> reader;
	reader->SetFileName("0.vtk");

	vtkNew<vtkPolyDataMapper> lineMapper;
	lineMapper->SetInputConnection(reader->GetOutputPort());

	vtkNew<vtkActor> lineActor;
	lineActor->SetMapper(lineMapper);
	lineActor->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());
	lineActor->GetProperty()->SetLineWidth(3.0);

	
	vtkNew<vtkImplicitModeller> imp;
	imp->SetInputConnection(reader->GetOutputPort());
	imp->SetSampleDimensions(110, 40, 20);
	imp->SetMaximumDistance(0.20);
	imp->SetModelBounds(-1.0, 9.0, -1.0, 3.0, -1.0, 1.0);

	vtkNew<vtkContourFilter> contour;
	contour->SetInputConnection(imp->GetOutputPort());
	contour->SetValue(0, 0.2);

	vtkNew<vtkPolyDataMapper> impMapper;
	impMapper->SetInputConnection(contour->GetOutputPort());
	impMapper->ScalarVisibilityOff();

	vtkNew<vtkActor> impActor;
	impActor->SetMapper(impMapper);
	impActor->GetProperty()->SetColor(colors->GetColor3d("CreamWhite").GetData());
	impActor->GetProperty()->SetOpacity(0.5);

	// Create renderer.
	vtkNew<vtkRenderer> ren1;
	vtkNew<vtkRenderWindow> renWin;
	renWin->AddRenderer(ren1);
	vtkNew<vtkRenderWindowInteractor> iren;
	iren->SetRenderWindow(renWin);

	// Add the actors to the renderer, set the background and size
	ren1->AddActor(lineActor);
	ren1->AddActor(impActor);
	ren1->SetBackground(colors->GetColor3d("Wheat").GetData());
	renWin->SetSize(700, 400);
	renWin->SetWindowName("Metu");

	vtkNew<vtkCamera> camera;
	camera->SetFocalPoint(4.5, 1, 0);
	camera->SetPosition(4.5, 1.0, 6.0);
	camera->SetViewUp(0, 1, 0);

	ren1->SetActiveCamera(camera);
	ren1->ResetCamera();
	camera->Dolly(1.3);
	camera->SetClippingRange(1.0, 90.0);//set the location of the far and near clipping planes

	renWin->Render();
	iren->Start();
	return EXIT_SUCCESS;
}*/


/**********************************************************************
*******************************************************************/
/*
// THE SECOND PART: EXPLICIT SURFACE RECONSTRUCTION


#include <vtkCamera.h>
#include <vtkCleanPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkDelaunay3D.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkOBJReader.h>


int main(int argc, char* argv[])
{	
	//read the file
	vtkNew<vtkXMLPolyDataReader> reader;// for .vtp
	//vtkNew<vtkPolyDataReader> reader;//for .vtk
	//vtkNew<vtkOBJReader> reader;//for .obj
	reader->SetFileName("1.vtp");
	vtkNew<vtkNamedColors> color;
	vtkNew<vtkDataSetMapper> mapper;
	mapper->SetInputConnection(reader->GetOutputPort());

	//vtkNew<vtkActor> actor;
	//actor->SetMapper(mapper);
	//actor->GetProperty()->SetColor(color->GetColor3d("green").GetData());
	//actor->GetProperty()->SetInterpolationToFlat();//for shading

	// Clean the polydata from duplicate points.
	vtkNew<vtkCleanPolyData> cleaner;
	cleaner->SetInputConnection(reader->GetOutputPort());

	// The goal here is to create an explicit surface, and by definition of explicit surface
	// points will be interpolated so connect sample points by triangles .
	vtkNew<vtkDelaunay3D> explicitt;
	explicitt->SetInputConnection(cleaner->GetOutputPort());
	explicitt->SetAlpha(0.03);//distance value to control output
	explicitt->Update();
	vtkNew<vtkDataSetMapper> explicitMapper;
	explicitMapper->SetInputConnection(explicitt->GetOutputPort());
	vtkNew<vtkActor> explicitActor;
	explicitActor->SetMapper(explicitMapper);
	explicitActor->GetProperty()->SetColor(color->GetColor3d("yellow").GetData());
	explicitActor->GetProperty()->SetInterpolationToFlat();

	// Create a renderer, render window, and interactor
	vtkNew<vtkRenderer> explicitRenderer;
	vtkNew<vtkRenderWindow> renderWindow;
	renderWindow->SetSize(700, 400);
	renderWindow->SetWindowName("Explicit Surface");

	renderWindow->AddRenderer(explicitRenderer);
	vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
	renderWindowInteractor->SetRenderWindow(renderWindow);
	
	//explicitRenderer->AddActor(actor);
	explicitRenderer->AddActor(explicitActor);
	explicitRenderer->SetBackground(color->GetColor3d("white").GetData());
	explicitRenderer->ResetCamera();
	renderWindow->Render();

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
*/

/***********************************************************
*************************************************************/

// THIRD PART: IMPLICIT SURFACE RECONSTRUCTION


#include <vtkActor.h>
#include <vtkContourFilter.h>
#include <vtkImplicitModeller.h>
#include <vtkNamedColors.h>
#include <vtkOBJReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char* argv[])
{
	vtkNew<vtkXMLPolyDataReader> reader;
	//vtkNew<vtkOBJReader> reader;
	reader->SetFileName("1.vtp");
	reader->Update();
	vtkNew<vtkNamedColors> colors;

	vtkNew<vtkImplicitModeller> implicit;
	implicit->SetSampleDimensions(50, 50, 50);
	implicit->SetInputData(reader->GetOutput());
	implicit->AdjustBoundsOn();
	implicit->SetAdjustDistance(.1);
	implicit->SetMaximumDistance(.1);

	// Compute the range for a contour value
	double bounds[6];
	reader->GetOutput() -> GetBounds(bounds);
	double xrange = bounds[1] - bounds[0];

	// Create the 0 isosurface
	vtkNew<vtkContourFilter> contourFilter;
	contourFilter->SetInputConnection(implicit->GetOutputPort());
	contourFilter->SetValue(0, xrange /30.0); 

											   
	vtkNew<vtkRenderer> renderer;
	vtkNew<vtkRenderWindow> renderWindow;
	renderWindow->AddRenderer(renderer);
	vtkNew<vtkRenderWindowInteractor> interactor;
	interactor->SetRenderWindow(renderWindow);

	vtkNew<vtkPolyDataMapper> mapper;
	mapper->SetInputConnection(contourFilter->GetOutputPort());
	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(colors->GetColor3d("red").GetData());
	renderer->AddActor(actor);
	renderer->SetBackground(colors->GetColor3d("white").GetData());

	renderWindow->SetSize(700, 400);
	renderWindow->SetWindowName("ImplicitModeller");

	renderWindow->Render();
	interactor->Start();

	return EXIT_SUCCESS;
}

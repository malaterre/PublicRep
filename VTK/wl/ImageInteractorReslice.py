#!/usr/bin/env python

# A simple vtkInteractorStyleImage example for
# 3D image viewing with the vtkImageResliceMapper.

# Drag Left mouse button to window/level
# Shift-Left drag to rotate (oblique slice)
# Shift-Middle drag to slice through image
# OR Ctrl-Right drag to slice through image

import vtk
from vtk.util.misc import vtkGetDataRoot
VTK_DATA_ROOT = vtkGetDataRoot()

reader = vtk.vtkImageReader()
reader.ReleaseDataFlagOff()
reader.SetDataByteOrderToLittleEndian()
reader.SetDataMask(0x7fff)
reader.SetDataExtent(0,63,0,63,1,93)
reader.SetDataSpacing(3.2,3.2,1.5)
reader.SetFilePrefix("" + str(VTK_DATA_ROOT) + "/Data/headsq/quarter")

renWin = vtk.vtkRenderWindow()
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

for i in range(0,3):
  print i
  # Create the RenderWindow, Renderer
  ren1 = vtk.vtkRenderer()
  ren1.SetBackground(0.1,0.2,0.4);
  if i == 0:
    ren1.SetViewport(0., 0., 0.333, 1);
  elif i == 1:
    ren1.SetViewport(0.333, 0., 0.667, 1);
  elif i == 2:
    ren1.SetViewport(0.667, 0., 1., 1.);
  renWin.AddRenderer(ren1)
  
  im = vtk.vtkImageResliceMapper()
  im.SetInputConnection(reader.GetOutputPort())
  im.SliceFacesCameraOn()
  im.SliceAtFocalPointOn()
  im.BorderOff()
  
  ip = vtk.vtkImageProperty()
  ip.SetColorWindow(2000)
  ip.SetColorLevel(1000)
  ip.SetAmbient(0.0)
  ip.SetDiffuse(1.0)
  ip.SetOpacity(1.0)
  ip.SetInterpolationTypeToLinear()
  
  bounds = im.GetBounds()
  print bounds
  point = [ 0.5*(bounds[0] + bounds[1]),
  0.5*(bounds[2] + bounds[3]),
  0.5*(bounds[4] + bounds[5])
  ]
  print point

  camera = ren1.GetActiveCamera()
  camera.SetFocalPoint(point)
  point[2] += 50.0
  camera.SetPosition(point)
  camera.ParallelProjectionOn()
  camera.SetParallelScale(5.0)

  ia = vtk.vtkImageSlice()
  ia.SetMapper(im)
  ia.SetProperty(ip)
  
  ren1.AddViewProp(ia)
  ren1.SetBackground(0.1,0.2,0.4)
  renWin.SetSize(300,300)
  

def CharCallback(obj, event):
    iren = renWin.GetInteractor()
    keycode = iren.GetKeyCode()
    if keycode == "s":
        #style.StartSpin();
        style.StartWindowLevel();
        return
    if keycode == "a":
        #style.EndSpin();
        style.EndWindowLevel();
        return

style = vtk.vtkInteractorStyleImage()
style.SetInteractionModeToImage3D()

iren.SetInteractorStyle(style)
iren.AddObserver("CharEvent", CharCallback)
renWin.SetInteractor(iren)

# render the image
renWin.Render()
cam1 = ren1.GetActiveCamera()
cam1.ParallelProjectionOn()
ren1.ResetCameraClippingRange()
renWin.Render()

iren.Start()

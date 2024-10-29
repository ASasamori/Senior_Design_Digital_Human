# BUtLAR: Voice-Powered Digital Human Assistant

## Contributors

**Noa Margolin¹**, **Suhani Mitra²**, **Jackie Salamy³**, **Andrew Sasamori⁴**

¹ [Department of Electrical and Computer Engineering](https://www.bu.edu/eng/departments/ece/), Boston University, Boston, MA, 02215  
Email: [noam@bu.edu](mailto:noam@bu.edu)

² [Department of Electrical and Computer Engineering](https://www.bu.edu/eng/departments/ece/), [Department of Computer Science](https://www.bu.edu/cs/), [Department of Mathematics and Statistics](https://www.bu.edu/math/) Boston University, Boston, MA, 02215  
Email: [suhanim@bu.edu](mailto:suhanim@bu.edu)

³ [Department of Electrical and Computer Engineering](https://www.bu.edu/eng/departments/ece/), Boston University, Boston, MA, 02215  
Email: [jesalamy@bu.edu](mailto:jesalamy@bu.edu)

⁴ [Department of Electrical and Computer Engineering](https://www.bu.edu/eng/departments/ece/), Boston University, Boston, MA, 02215  
Email: [sasamori@bu.edu](mailto:sasamori@bu.edu)

---

[**Command Lines**]
Here are the commands to run:
----------------------------------------------------------------------------------------------------
sudo apt install build-essential clang

 tar -xvf YobeSDK-Release-GrandE-0.6.2-Linux.tar.gz

cd  YobeSDK-Release-GrandE-0.6.2-Linux

chmod +x install.sh

sudo ./install.sh D18F38-BC2D17-E709EA-3782C3-8D923E-V3

cd samples

CC=clang CXX=clang++ cmake -B build

cmake --build build

./build/BioListener_demo ./audio_files/BioListener/BioListener_test.wav end-fire near-field "student-pc" ./build

./build/IDListener_demo ./audio_files/IDListener/IDListener_test.wav end-fire no-target "student-pc" ./build

----------------------------------------------------------------------------------------------------

Let me know if you run into any issues,
Jake


[**Yobe**](https://yobeinc.com/), 77 Franklin St, Boston, MA 02110  
Phone: (617) 848 8922  
Email: [contact.us@yobeinc.com](mailto:contact.us@yobeinc.com)

## Internal Links:
[Shared Drive](https://drive.google.com/drive/u/1/folders/0APRJN7ri7rJUUk9PVA)

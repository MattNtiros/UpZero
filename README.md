# Up Zero Component

This component takes a signal as an input and upsamples the signal by a given factor. The upsampling is performed by the addition of zeros in between the samples of the signal. This component is compatable with both real and complex signals.

## Building & Installation
    ./reconf
    ./configure
    make -j
    sudo make install

## Notes

This component takes a float as input and produces a float as output. There is one property of the component: upsample_factor. This is the factor by which the signal is upsampled, and thus output will contain upsample_factor times as many elements as the input. If the input signal is real, UpZero will insert real 0's in between samples, whereas if the input is complex, UpSample will insert complex zeros (i.e. (0, 0)).

## Copyrights

This work is protected by Copyright. Copyright information is included on all files within the component.

## Liscense

The Real Part Component is licensed under the Lesser GNU General Public License (LGPL).

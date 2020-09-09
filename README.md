# CAtomic
C11 stdatomic binding for Swift and ObjC.

## Usage

### Swift

```swift
var count = CAtomicLLong(value: 0)
count.fetchAdd(1)
```

### ObjC

```ObjC
CAtomicLong *count = [[CAtomicLong alloc] initWithValue:99];
[count fetchAdd:1];
```

### ObjC++
```cpp
auto count = new CAtomic<NSInteger>(99);
count->fetchAdd(1);
```

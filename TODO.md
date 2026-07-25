# MCR TODOs

## Build some fraggin' tests

As I think of useful test cases I'll try to document them here.

### Insert
- Insert into empty scroll at index 0
- Insert at beginning of scroll with data
- Insert into middle of scroll
- Insert at span (not push)
- Insert while resize is required
- Insert when index > span (should fail)

### Remove
- Remove from empty scroll (should fail)
- Remove first element
- Remove middle element
- Remove final element
- Remove only element
- Remove while span == limit
- Remove when index == span
